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

class npc_huntervendor : public CreatureScript
{
public:
    npc_huntervendor() : CreatureScript("npc_huntervendor") { }

    bool OnGossipHello(Player *pPlayer, Creature *pCreature)
    {
        if(pPlayer->getClass() == CLASS_HUNTER)
	 {
            pPlayer->GetSession()->SendListInventory(pCreature->GetGUID());
	 } else {
            pPlayer->PlayerTalkClass->SendCloseGossip();
            pCreature->MonsterWhisper("Your not a HUNTER, i cant sell to you $N!", pPlayer->GetGUID());
	 }

        return true;
    }

    bool OnGossipSelect(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        if(!pPlayer->getAttackers().empty())
        {
            pPlayer->PlayerTalkClass->SendCloseGossip();
            pCreature->MonsterWhisper("I will not sell items to you $N when your in a fight!",pPlayer->GetGUID());
        }
        return true;
    }
};

void AddSC_npc_huntervendor()
{
    new npc_huntervendor();
}