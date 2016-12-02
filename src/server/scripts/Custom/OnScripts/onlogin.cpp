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

#include "ScriptPCH.h"

#define SONG 11466

class on_login : public PlayerScript
{
    public:
        on_login() : PlayerScript("on_login") {}

    void OnLogin(Player* player)
    {
            ChatHandler(player->GetSession()).PSendSysMessage("Welcome back! Your character has been saved, healed and is all ready to go!");
	     player->GetSession()->SendNotification("WELCOME BACK ONLINE ");
	     player->GetSession()->SendNotification("! %s !", player->GetName());

	     player->SetXpRate(1);	     

	     if (player->GetMap()->IsBattlegroundOrArena())
	     {
	     	  player->ResurrectPlayer(0.5f);
	         player->TeleportTo(534, 5541.770020f, -3783.469971f, 1594.910034f, 2.883010f);
	     }

	     /*QueryResult result = CharacterDatabase.PQuery("SELECT first_login FROM characters WHERE guid = '%u'", player->GetGUID());
 
	     Field* fields = result->Fetch();
	     uint8 flag = fields[0].GetUInt8();

            if (player->HasFlag)
            {
		  player->CastSpell(player, 11543, 1);
		  player->PlayDirectSound(11466, player);
		  CharacterDatabase.PExecute("UPDATE characters set first_login = 1 WHERE guid = '%u'", player->GetGUID());
            }*/
    }
};

void AddSC_on_login()
{
    new on_login();
}