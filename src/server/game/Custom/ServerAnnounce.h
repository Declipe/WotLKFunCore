/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
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

#ifndef SERVER_ANNOUNCE_H_
#define SERVER_ANNOUNCE_H_
#include "Common.h"
#include "DatabaseEnv.h"
#include "World.h"
#include "Player.h"
#include "Opcodes.h"
#include "Chat.h"
#include "ObjectAccessor.h"
#include "Language.h"
#include "AccountMgr.h"
#include "SystemConfig.h"
#include "revision.h"
#include "Util.h"

class ServerAnnounce
{
public:
/*
        static void AnnounceBan(const char * tempAuthor, std::string & target, const char * tempReason);
        static void AnnounceBan(const char * tempAuthor, std::string & target, const char * tempReason, std::string duration);
        static void AnnounceMute(const char * tempAuthor, std::string & target, std::string & reason);
        static void AnnounceMute(const char * tempAuthor, std::string & target, std::string & reason, std::string duration);
        static void AnnounceKick(const char * tempAuthor, std::string & target);
        static void AnnounceKick(const char * tempAuthor, std::string & target, std::string & reason);
	*/
        static void AnnounceBan(const char* tempAuthor, std::string target, const char* tempReason);
        static void AnnounceBan(const char* tempAuthor, std::string target, const char* tempReason, std::string duration);
        static void AnnounceMute(const char* tempAuthor, std::string target, std::string reason);
        static void AnnounceMute(const char* tempAuthor, std::string target, std::string reason, std::string duration);
        static void AnnounceKick(const char* tempAuthor, std::string target);
        static void AnnounceKick(const char* tempAuthor, std::string target, std::string reason);
};
#endif