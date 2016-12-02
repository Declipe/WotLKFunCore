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
#include "Chat.h"

class item_spawn_teleporter : public ItemScript
{
public:
	item_spawn_teleporter() : ItemScript("item_spawn_teleporter") { }

	bool OnUse(Player* player, Item* item)
	{
  		player->SummonCreature(481851,player->GetPositionX() ,player->GetPositionY()+10, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,30000);
		ChatHandler(player->GetSession()).PSendSysMessage("The Teleporter has been spawened, you have 30 seconds to choose a destination.");
  		return true;
	}

};

void AddSC_item_spawn_teleporter()
{
	new item_spawn_teleporter();
}