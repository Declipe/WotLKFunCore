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

class OnEnterMap: public PlayerScript
{
    public:
        OnEnterMap() : PlayerScript("OnEnterMap") {}

    void OnPlayerEnterMap(Map* map, Player* player)
    {
    	if (player->GetMapId() == 532 && (player->GetCommandStatus(CHEAT_COOLDOWN) || player->GetCommandStatus(CHEAT_CASTTIME)))
    	{
		player->m_CheatCastTime = false;
		player->m_CheatCooldown = false;
    	}
    }
};

void AddSC_OnEnterMap()
{
    new OnEnterMap();
}