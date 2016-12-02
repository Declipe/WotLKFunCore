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

class player_berserking : public CreatureScript
{
    public:

        player_berserking()
            : CreatureScript("player_berserking")
        {
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
	     if(!pPlayer->HasAura(68378))
	     {
              if(pPlayer->GetSession()->GetSecurity() >= 1)
		{
            	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP BERSERKING - 1 VP", GOSSIP_SENDER_MAIN, 1002);
            	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP BERSERKING - 10 Event Coins", GOSSIP_SENDER_MAIN, 1004);
		} else {
            	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "PLAYER BERSERKING - 2 VP", GOSSIP_SENDER_MAIN, 1000);
            	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "PLAYER BERSERKING - 20 Event Coins", GOSSIP_SENDER_MAIN, 1003);
		}
            	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 1001);
            	pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());

	     } else {
	     	ChatHandler(pPlayer).PSendSysMessage("You are already berserking.");
            	pPlayer->PlayerTalkClass->SendCloseGossip();
	     }

            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();


            switch (uiAction)
            {
            case 1000:
		  if(pPlayer->HasItemCount(40753, 2))
		  {
                pPlayer->AddAura(68378, pPlayer);
		  pPlayer->DestroyItemCount(40753, 2, true);
                ChatHandler(pPlayer).PSendSysMessage("YOU ARE NOW BERSERKING UNTIL YOU LEAVE THIS INSTANCE!");
		  pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
		  ChatHandler(pPlayer).PSendSysMessage("To get berserked like this you need 2 Emblem of Voting.");
		  pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;

            case 1002:
		  if(pPlayer->HasItemCount(40753, 1))
		  {
                pPlayer->AddAura(68378, pPlayer);
		  pPlayer->DestroyItemCount(40753, 1, true);
                ChatHandler(pPlayer).PSendSysMessage("YOU ARE NOW BERSERKING UNTIL YOU LEAVE THIS INSTANCE!");
		  pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
		  ChatHandler(pPlayer).PSendSysMessage("To get berserked like this you need 1 Emblem of Voting.");
		  pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;

            case 1003:
		  if(pPlayer->HasItemCount(23247, 20))
		  {
                pPlayer->AddAura(68378, pPlayer);
		  pPlayer->DestroyItemCount(23247, 20, true);
                ChatHandler(pPlayer).PSendSysMessage("YOU ARE NOW BERSERKING UNTIL YOU LEAVE THIS INSTANCE!");
		  pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
		  ChatHandler(pPlayer).PSendSysMessage("To get berserked like this you need 20 Event Coins.");
		  pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;

            case 1004:
		  if(pPlayer->HasItemCount(23247, 10))
		  {
                pPlayer->AddAura(68378, pPlayer);
		  pPlayer->DestroyItemCount(23247, 10, true);
                ChatHandler(pPlayer).PSendSysMessage("YOU ARE NOW BERSERKING UNTIL YOU LEAVE THIS INSTANCE!");
		  pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
		  ChatHandler(pPlayer).PSendSysMessage("To get berserked like this you need 10 Event Coins.");
		  pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;

		case 1001:
			pCreature->MonsterSay("Come again anytime you wish to get ZERKED!", LANG_UNIVERSAL, NULL);
			pPlayer->PlayerTalkClass->SendCloseGossip();
			break;

            }


            return true;
        }

};

void AddSC_player_beserking()
{
   new player_berserking();
}