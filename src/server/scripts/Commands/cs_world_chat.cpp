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

#include "ScriptPCH.h"
#include "Chat.h"

class cs_world_chat : public CommandScript
{
	public:
		cs_world_chat() : CommandScript("cs_world_chat"){}

	ChatCommand * GetCommands() const
	{
		static ChatCommand WorldChatCommandTable[] = 
		{
			{"chat",	SEC_PLAYER,		true,		&HandleWorldChatCommand,	"", NULL},
			{NULL,		0,				false,		NULL,						"", NULL}
		};

		return WorldChatCommandTable;
	}

	static bool HandleWorldChatCommand(ChatHandler * handler, const char * args)
	{
		std::string msg = "";
		Player * player = handler->GetSession()->GetPlayer();

			if (player->GetSession()->GetSecurity() == 1)
			{
				msg += "|cff00ffff[VIP] |cff00ffff[";
				msg += player->GetName();
				msg += "] |cff00ccff";
			}
			if (player->GetSession()->GetSecurity() >= 2)
			{
				msg += "|cff00ffff[Staff] |cff00ffff[";
				msg += player->GetName();
				msg += "] |cff00ccff";
			}
		else
		{
			if (player->GetTeam() == ALLIANCE)
			{
				msg += "|cff0000ff[A] |cffffffff[";
				msg += player->GetName();
				msg += "] |cff00ccff";
			}

			if (player->GetTeam() == HORDE)
			{
				msg += "|cffff0000[H] |cffffffff[";
				msg += player->GetName();
				msg += "] |cff00ccff";
			}
		}
			
		msg += args;
		sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);	

		return true;
	}
};

void AddSC_cs_world_chat()
{
	new cs_world_chat();
}