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

#ifndef _TRANSACTION_H
#define _TRANSACTION_H

#include "SQLOperation.h"

//- Forward declare (don't include header to prevent circular includes)
class PreparedStatement;

/*! Transactions, high level class. */
class Transaction
{
    friend class TransactionTask;
    friend class MySQLConnection;

    public:
        Transaction() : _cleanedUp(false) {}
        ~Transaction() { Cleanup(); }

        void Append(PreparedStatement* statement);
        void Append(const char* sql);
        void PAppend(const char* sql, ...);

        size_t GetSize() const { return m_queries.size(); }

    protected:
        void Cleanup();
        std::list<SQLElementData> m_queries;

    private:
        bool _cleanedUp;

};
typedef Trinity::AutoPtr<Transaction, ACE_Thread_Mutex> SQLTransaction;

/*! Low level class*/
class TransactionTask : public SQLOperation
{
    template <class T> friend class DatabaseWorkerPool;
    friend class DatabaseWorker;

    public:
        TransactionTask(SQLTransaction trans) : m_trans(trans) {} ;
        ~TransactionTask(){};

    protected:
        bool Execute();

        SQLTransaction m_trans;
};

#endif