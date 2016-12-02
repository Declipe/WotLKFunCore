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

#ifndef _MAP_UPDATER_H_INCLUDED
#define _MAP_UPDATER_H_INCLUDED

#include <ace/Thread_Mutex.h>
#include <ace/Condition_Thread_Mutex.h>

#include "DelayExecutor.h"

class Map;

class MapUpdater
{
    public:

        MapUpdater();
        virtual ~MapUpdater();

        friend class MapUpdateRequest;

        int schedule_update(Map& map, ACE_UINT32 diff);

        int wait();

        int activate(size_t num_threads);

        int deactivate();

        bool activated();

    private:

        DelayExecutor m_executor;
        ACE_Thread_Mutex m_mutex;
        ACE_Condition_Thread_Mutex m_condition;
        size_t pending_requests;

        void update_finished();
};

#endif //_MAP_UPDATER_H_INCLUDED
