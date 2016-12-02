/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2006-2016 ScriptDev2.
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

/* ScriptData
SDName: Felwood
SD%Complete: 95
SDComment: Quest support: 4101, 4102
SDCategory: Felwood
EndScriptData */

/* ContentData
npcs_riverbreeze_and_silversky
EndContentData */

#include "ScriptPCH.h"

/*######
## npcs_riverbreeze_and_silversky
######*/

#define GOSSIP_ITEM_BEACON  "Please make me a Cenarion Beacon"

class npcs_riverbreeze_and_silversky : public CreatureScript
{
public:
    npcs_riverbreeze_and_silversky() : CreatureScript("npcs_riverbreeze_and_silversky") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();
            creature->CastSpell(player, 15120, false);
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        uint32 creatureId = creature->GetEntry();

        if (creatureId == 9528)
        {
            if (player->GetQuestRewardStatus(4101))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BEACON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU(2848, creature->GetGUID());
            } else if (player->GetTeam() == HORDE)
            player->SEND_GOSSIP_MENU(2845, creature->GetGUID());
            else
                player->SEND_GOSSIP_MENU(2844, creature->GetGUID());
        }

        if (creatureId == 9529)
        {
            if (player->GetQuestRewardStatus(4102))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BEACON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU(2849, creature->GetGUID());
            } else if (player->GetTeam() == ALLIANCE)
            player->SEND_GOSSIP_MENU(2843, creature->GetGUID());
            else
                player->SEND_GOSSIP_MENU(2842, creature->GetGUID());
        }

        return true;
    }
};

void AddSC_felwood()
{
    new npcs_riverbreeze_and_silversky();
}
