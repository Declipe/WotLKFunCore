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

#include "AdhocStatement.h"
#include "MySQLConnection.h"

/*! Basic, ad-hoc queries. */
BasicStatementTask::BasicStatementTask(const char* sql) :
m_has_result(false)
{
    m_sql = strdup(sql);
}

BasicStatementTask::BasicStatementTask(const char* sql, QueryResultFuture result) :
m_has_result(true),
m_result(result)
{
    m_sql = strdup(sql);
}

BasicStatementTask::~BasicStatementTask()
{
    free((void*)m_sql);
}

bool BasicStatementTask::Execute()
{
    if (m_has_result)
    {
        ResultSet* result = m_conn->Query(m_sql);
        if (!result || !result->GetRowCount())
        {
            delete result;
            m_result.set(QueryResult(NULL));
            return false;
        }
        result->NextRow();
        m_result.set(QueryResult(result));
        return true;
    }

    return m_conn->Execute(m_sql);
}
