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

#include "DatabaseEnv.h"
#include "DatabaseWorker.h"
#include "SQLOperation.h"
#include "MySQLConnection.h"
#include "MySQLThreading.h"

DatabaseWorker::DatabaseWorker(ACE_Activation_Queue* new_queue, MySQLConnection* con) :
m_queue(new_queue),
m_conn(con)
{
    /// Assign thread to task
    activate();
}

int DatabaseWorker::svc()
{
    if (!m_queue)
        return -1;

    SQLOperation *request = NULL;
    while (1)
    {
        request = (SQLOperation*)(m_queue->dequeue());
        if (!request)
            break;

        request->SetConnection(m_conn);
        request->call();

        delete request;
    }

    return 0;
}
