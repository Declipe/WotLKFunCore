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

/** \file
    \ingroup u2w
*/

#include "WorldLog.h"
#include "Config.h"
#include "Log.h"
#include "DatabaseWorkerPool.h"

WorldLog::WorldLog() : i_file(NULL)
{
    Initialize();
}

WorldLog::~WorldLog()
{
    if (i_file != NULL)
        fclose(i_file);

    i_file = NULL;
}

/// Open the log file (if specified so in the configuration file)
void WorldLog::Initialize()
{
    std::string logsDir = ConfigMgr::GetStringDefault("LogsDir", "");

    if (!logsDir.empty())
    {
        if ((logsDir.at(logsDir.length()-1) != '/') && (logsDir.at(logsDir.length()-1) != '\\'))
            logsDir.push_back('/');
    }

    std::string logname = ConfigMgr::GetStringDefault("WorldLogFile", "");
    if (!logname.empty())
    {
        i_file = fopen((logsDir+logname).c_str(), "w");
    }

    m_dbWorld = ConfigMgr::GetBoolDefault("LogDB.World", false); // can be VERY heavy if enabled
}

void WorldLog::outTimestampLog(char const* fmt, ...)
{
    if (LogWorld())
    {
        TRINITY_GUARD(ACE_Thread_Mutex, Lock);
        ASSERT(i_file);

        Log::outTimestamp(i_file);
        va_list args;
        va_start(args, fmt);
        vfprintf(i_file, fmt, args);
        //fprintf(i_file, "\n");
        va_end(args);

        fflush(i_file);
    }

    if (sLog->GetLogDB() && m_dbWorld)
    {
        va_list ap2;
        va_start(ap2, fmt);
        char nnew_str[MAX_QUERY_LEN];
        vsnprintf(nnew_str, MAX_QUERY_LEN, fmt, ap2);
        sLog->outDB(LOG_TYPE_WORLD, nnew_str);
        va_end(ap2);
    }
}

void WorldLog::outLog(char const* fmt, ...)
{
    if (LogWorld())
    {
        TRINITY_GUARD(ACE_Thread_Mutex, Lock);
        ASSERT(i_file);

        va_list args;
        va_start(args, fmt);
        vfprintf(i_file, fmt, args);
        //fprintf(i_file, "\n");
        va_end(args);

        fflush(i_file);
    }

    if (sLog->GetLogDB() && m_dbWorld)
    {
        va_list ap2;
        va_start(ap2, fmt);
        char nnew_str[MAX_QUERY_LEN];
        vsnprintf(nnew_str, MAX_QUERY_LEN, fmt, ap2);
        sLog->outDB(LOG_TYPE_WORLD, nnew_str);
        va_end(ap2);
    }
}
