/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
*
* ==== Start of GNU GPL ====
*
* This file is free software; as a special exception the author gives
* unlimited permission to copy and/or distribute it, with or without
* modifications, as long as this notice is preserved.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* ==== End of GNU GPL ====
*/

#include "MySQLConnection.h"
#include "QueryHolder.h"
#include "PreparedStatement.h"
#include "Log.h"

bool SQLQueryHolder::SetQuery(size_t index, const char *sql)
{
    if (m_queries.size() <= index)
    {
        sLog->outError("Query index (%zu) out of range (size: %u) for query: %s", index, (uint32)m_queries.size(), sql);
        return false;
    }

    /// not executed yet, just stored (it's not called a holder for nothing)
    SQLElementData element;
    element.type = SQL_ELEMENT_RAW;
    element.element.query = strdup(sql);

    SQLResultSetUnion result;
    result.qresult = NULL;

    m_queries[index] = SQLResultPair(element, result);
    return true;
}

bool SQLQueryHolder::SetPQuery(size_t index, const char *format, ...)
{
    if (!format)
    {
        sLog->outError("Query (index: %zu) is empty.", index);
        return false;
    }

    va_list ap;
    char szQuery [MAX_QUERY_LEN];
    va_start(ap, format);
    int res = vsnprintf(szQuery, MAX_QUERY_LEN, format, ap);
    va_end(ap);

    if (res == -1)
    {
        sLog->outError("SQL Query truncated (and not execute) for format: %s", format);
        return false;
    }

    return SetQuery(index, szQuery);
}

bool SQLQueryHolder::SetPreparedQuery(size_t index, PreparedStatement* stmt)
{
    if (m_queries.size() <= index)
    {
        sLog->outError("Query index (%zu) out of range (size: %u) for prepared statement", index, (uint32)m_queries.size());
        return false;
    }

    /// not executed yet, just stored (it's not called a holder for nothing)
    SQLElementData element;
    element.type = SQL_ELEMENT_PREPARED;
    element.element.stmt = stmt;

    SQLResultSetUnion result;
    result.presult = NULL;

    m_queries[index] = SQLResultPair(element, result);
    return true;
}

QueryResult SQLQueryHolder::GetResult(size_t index)
{
    // Don't call to this function if the index is of an ad-hoc statement
    if (index < m_queries.size())
    {
        ResultSet* result = m_queries[index].second.qresult;
        if (!result || !result->GetRowCount())
            return QueryResult(NULL);

        result->NextRow();
        return QueryResult(result);
    }
    else
        return QueryResult(NULL);
}

PreparedQueryResult SQLQueryHolder::GetPreparedResult(size_t index)
{
    // Don't call to this function if the index is of a prepared statement
    if (index < m_queries.size())
    {
        PreparedResultSet* result = m_queries[index].second.presult;
        if (!result || !result->GetRowCount())
            return PreparedQueryResult(NULL);

        return PreparedQueryResult(result);
    }
    else
        return PreparedQueryResult(NULL);
}

void SQLQueryHolder::SetResult(size_t index, ResultSet* result)
{
    if (result && !result->GetRowCount())
    {
        delete result;
        result = NULL;
    }

    /// store the result in the holder
    if (index < m_queries.size())
        m_queries[index].second.qresult = result;
}

void SQLQueryHolder::SetPreparedResult(size_t index, PreparedResultSet* result)
{
    if (result && !result->GetRowCount())
    {
        delete result;
        result = NULL;
    }

    /// store the result in the holder
    if (index < m_queries.size())
        m_queries[index].second.presult = result;
}

SQLQueryHolder::~SQLQueryHolder()
{
    for (size_t i = 0; i < m_queries.size(); i++)
    {
        /// if the result was never used, free the resources
        /// results used already (getresult called) are expected to be deleted
        if (SQLElementData* data = &m_queries[i].first)
        {
            switch (data->type)
            {
                case SQL_ELEMENT_RAW:
                    free((void*)(const_cast<char*>(data->element.query)));
                    break;
                case SQL_ELEMENT_PREPARED:
                    delete data->element.stmt;
                    break;
            }
        }
    }
}

void SQLQueryHolder::SetSize(size_t size)
{
    /// to optimize push_back, reserve the number of queries about to be executed
    m_queries.resize(size);
}

bool SQLQueryHolderTask::Execute()
{
    if (!m_holder)
        return false;

    /// we can do this, we are friends
    std::vector<SQLQueryHolder::SQLResultPair> &queries = m_holder->m_queries;

    for (size_t i = 0; i < queries.size(); i++)
    {
        /// execute all queries in the holder and pass the results
        if (SQLElementData* data = &queries[i].first)
        {
            switch (data->type)
            {
                case SQL_ELEMENT_RAW:
                {
                    char const* sql = data->element.query;
                    if (sql)
                        m_holder->SetResult(i, m_conn->Query(sql));
                    break;
                }
                case SQL_ELEMENT_PREPARED:
                {
                    PreparedStatement* stmt = data->element.stmt;
                    if (stmt)
                        m_holder->SetPreparedResult(i, m_conn->Query(stmt));
                    break;
                }
            }
        }
    }

    m_result.set(m_holder);
    return true;
}
