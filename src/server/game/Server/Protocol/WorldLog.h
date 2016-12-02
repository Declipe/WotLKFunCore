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

/// \addtogroup u2w
/// @{
/// \file

#ifndef TRINITY_WORLDLOG_H
#define TRINITY_WORLDLOG_H

#include "Common.h"
#include <ace/Singleton.h>
#include "Errors.h"

#include <stdarg.h>

/// %Log packets to a file
class WorldLog
{
    friend class ACE_Singleton<WorldLog, ACE_Thread_Mutex>;

    private:
        WorldLog();
        ~WorldLog();
        WorldLog(const WorldLog &);
        WorldLog& operator=(const WorldLog &);
        ACE_Thread_Mutex Lock;

    public:
        void Initialize();
        /// Is the world logger active?
        bool LogWorld(void) const { return (i_file != NULL); }
        /// %Log to the file
        void outLog(char const* fmt, ...);
        void outTimestampLog(char const* fmt, ...);

    private:
        FILE* i_file;

        bool m_dbWorld;
};

#define sWorldLog ACE_Singleton<WorldLog, ACE_Thread_Mutex>::instance()
#endif
/// @}

