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

/** \file
    \ingroup Trinityd
 */

#include "Common.h"
#include "Config.h"
#include "Log.h"
#include "RARunnable.h"
#include "World.h"

#include <ace/Reactor_Impl.h>
#include <ace/TP_Reactor.h>
#include <ace/Dev_Poll_Reactor.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>

#include "RASocket.h"

RARunnable::RARunnable()
{
    ACE_Reactor_Impl* imp = NULL;

#if defined (ACE_HAS_EVENT_POLL) || defined (ACE_HAS_DEV_POLL)
    imp = new ACE_Dev_Poll_Reactor();
    imp->max_notify_iterations (128);
    imp->restart (1);
#else
    imp = new ACE_TP_Reactor();
    imp->max_notify_iterations (128);
#endif

    m_Reactor = new ACE_Reactor (imp, 1);
}

RARunnable::~RARunnable()
{
    delete m_Reactor;
}

void RARunnable::run()
{
    if (!ConfigMgr::GetBoolDefault("Ra.Enable", false))
        return;

    ACE_Acceptor<RASocket, ACE_SOCK_ACCEPTOR> acceptor;

    uint16 raport = ConfigMgr::GetIntDefault("Ra.Port", 3443);
    std::string stringip = ConfigMgr::GetStringDefault("Ra.IP", "0.0.0.0");
    ACE_INET_Addr listen_addr(raport, stringip.c_str());

    if (acceptor.open(listen_addr, m_Reactor) == -1)
    {
        sLog->outError("Trinity RA can not bind to port %d on %s", raport, stringip.c_str());
        return;
    }

    sLog->outString("Starting Trinity RA on port %d on %s", raport, stringip.c_str());

    while (!World::IsStopped())
    {
        // don't be too smart to move this outside the loop
        // the run_reactor_event_loop will modify interval
        ACE_Time_Value interval(0, 100000);
        if (m_Reactor->run_reactor_event_loop(interval) == -1)
            break;
    }

    sLog->outStaticDebug("Trinity RA thread exiting");
}
