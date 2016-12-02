/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2005-2016 MaNGOS.
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

#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include "AutoPtr.h"
#include <ace/Thread_Mutex.h>

#include "Field.h"
#include "Log.h"

#ifdef _WIN32
  #include <winsock2.h>
#endif
#include <mysql.h>

class ResultSet
{
    public:
        ResultSet(MYSQL_RES* result, MYSQL_FIELD* fields, uint64 rowCount, uint32 fieldCount);
        ~ResultSet();

        bool NextRow();
        uint64 GetRowCount() const { return _rowCount; }
        uint32 GetFieldCount() const { return _fieldCount; }

        Field* Fetch() const { return _currentRow; }
        const Field & operator [] (uint32 index) const
        {
            ASSERT(index < _fieldCount);
            return _currentRow[index];
        }

    protected:
        uint64 _rowCount;
        Field* _currentRow;
        uint32 _fieldCount;

    private:
        void CleanUp();
        MYSQL_RES* _result;
        MYSQL_FIELD* _fields;
};

typedef Trinity::AutoPtr<ResultSet, ACE_Thread_Mutex> QueryResult;

class PreparedResultSet
{
    public:
        PreparedResultSet(MYSQL_STMT* stmt, MYSQL_RES* result, uint64 rowCount, uint32 fieldCount);
        ~PreparedResultSet();

        bool NextRow();
        uint64 GetRowCount() const { return m_rowCount; }
        uint32 GetFieldCount() const { return m_fieldCount; }

        Field* Fetch() const
        {
            ASSERT(m_rowPosition < m_rowCount);
            return m_rows[uint32(m_rowPosition)];
        }

        const Field & operator [] (uint32 index) const
        {
            ASSERT(m_rowPosition < m_rowCount);
            ASSERT(index < m_fieldCount);
            return m_rows[uint32(m_rowPosition)][index];
        }

    protected:
        std::vector<Field*> m_rows;
        uint64 m_rowCount;
        uint64 m_rowPosition;
        uint32 m_fieldCount;

    private:
        MYSQL_BIND* m_rBind;
        MYSQL_STMT* m_stmt;
        MYSQL_RES* m_res;

        my_bool* m_isNull;
        unsigned long* m_length;

        void FreeBindBuffer();
        void CleanUp();
        bool _NextRow();

};

typedef Trinity::AutoPtr<PreparedResultSet, ACE_Thread_Mutex> PreparedQueryResult;

#endif

