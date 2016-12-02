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

enum TransmogrifyActions {
    ACTION_TRANSMOGRIFY_ADD_DISPLAY,
    ACTION_TRANSMOGRIFY_REMOVE_DISPLAY,
    ACTION_TRANSMOGRIFY_SUPPLYS,
    ACTION_TRANSMOGRIFY_ADD_DISPLAY_TWO
};

class npc_transmogrify : public CreatureScript
{
    public:
        npc_transmogrify() : CreatureScript("npc_transmogrify") { }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Make exchange! 4 PvP Tickets", GOSSIP_SENDER_MAIN, ACTION_TRANSMOGRIFY_ADD_DISPLAY);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Make exchange! 1 Transmogrifaction Tokens", GOSSIP_SENDER_MAIN, ACTION_TRANSMOGRIFY_ADD_DISPLAY_TWO);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Make item clean.", GOSSIP_SENDER_MAIN, ACTION_TRANSMOGRIFY_REMOVE_DISPLAY);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Transmogrify Supplys", GOSSIP_SENDER_MAIN, ACTION_TRANSMOGRIFY_SUPPLYS);
            pPlayer->SEND_GOSSIP_MENU(51000, pCreature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->SendCloseGossip();
            switch (action)
            {
                case ACTION_TRANSMOGRIFY_ADD_DISPLAY:
                    TransmogrifyItem(player, creature);
                    break;
                case ACTION_TRANSMOGRIFY_ADD_DISPLAY_TWO:
                    TransmogrifyItemTwo(player, creature);
                    break;
                case ACTION_TRANSMOGRIFY_REMOVE_DISPLAY:
                    ClearItem(player, creature);
                    break;
				case ACTION_TRANSMOGRIFY_SUPPLYS:
					pPlayer->GetSession()->SendListInventory(creature->GetGUID());
					break;
            }
            return true;
        }

        void TransmogrifyItem(Player* player, Creature* creature)
        {
            ChatHandler handler(player);
            Item *trItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START);
            Item *displayItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START + 1);
            if (!trItem || !displayItem)
            {
                handler.PSendSysMessage("Put item in the first and second slot!");
                return;
            }
            if (!player->HasItemCount(19182, 4, true))
            {
                handler.PSendSysMessage("It costs 4 PvP Prize Tickets!");
                return;
            }

            uint8 result = trItem->SetFakeDisplay(displayItem->GetTemplate()->ItemId);
            switch (result)
            {
                case FAKE_ERR_CANT_FIND_ITEM:
                    handler.PSendSysMessage("Cant find item!");
                    break;
                case FAKE_ERR_OK:
                {
                    WorldPacket data;
                    data << uint8(INVENTORY_SLOT_BAG_0);
                    data << uint8(trItem->GetSlot());
                    player->GetSession()->HandleAutoEquipItemOpcode(data);

                    player->DestroyItemCount(19182, 4, true);
                    handler.PSendSysMessage("Item successfully transmogrified!!");

                    break;
                }
            }
        }

		void TransmogrifyItemTwo(Player* player, Creature* creature)
        {
            ChatHandler handler(player);
            Item *trItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START);
            Item *displayItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START + 1);
            if (!trItem || !displayItem)
            {
                handler.PSendSysMessage("Put item in the first and second slot!");
                return;
            }

            if (!player->HasItemCount(986504, 1, true))
            {
                handler.PSendSysMessage("It costs 1 Transmogrification Tokens!");
                return;
            }

            uint8 result = trItem->SetFakeDisplay(displayItem->GetTemplate()->ItemId);
            switch (result)
            {
                case FAKE_ERR_CANT_FIND_ITEM:
                    handler.PSendSysMessage("Cant find item!");
                    break;
                case FAKE_ERR_OK:
                {
                    WorldPacket data;
                    data << uint8(INVENTORY_SLOT_BAG_0);
                    data << uint8(trItem->GetSlot());
                    player->GetSession()->HandleAutoEquipItemOpcode(data);

                    player->DestroyItemCount(986504, 1, true);
                    handler.PSendSysMessage("Item successfully transmogrified!!");

                    break;
                }
            }
        }

        void ClearItem(Player *player, Creature* creature)
        {
            ChatHandler handler(player);
            Item *trItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START);
            if (!trItem)
            {
                handler.PSendSysMessage("Put item in the first slot!");
                return;
            }

            trItem->RemoveFakeDisplay();

            WorldPacket data;
            data << uint8(INVENTORY_SLOT_BAG_0);
            data << uint8(trItem->GetSlot());
            player->GetSession()->HandleAutoEquipItemOpcode(data);

            handler.PSendSysMessage("Item successfully cleared!!");
        }
};

void AddSC_Transmogrification()
{
    new npc_transmogrify;
}