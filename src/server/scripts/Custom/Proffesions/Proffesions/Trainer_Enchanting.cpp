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

class Trainer_Enchanting : public CreatureScript
{
public:
	Trainer_Enchanting()
		: CreatureScript("Trainer_Enchanting")
	{
	}

	struct Trainer_EnchantingAI : public ScriptedAI
	{
		Trainer_EnchantingAI(Creature *c) : ScriptedAI(c)
		{
		}

		void Reset()
		{
			me->RestoreFaction();
		}

		void EnterEvadeMode()
        {
            me->GetMotionMaster()->Clear();
            ScriptedAI::EnterEvadeMode();
        }

	};

	CreatureAI* GetAI(Creature* pCreature) const
    {
		return new Trainer_EnchantingAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Enchanting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(51313) == true)
				{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Enchant Ring - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		}
		pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
	}

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
		MainMenu(pPlayer, pCreature);

        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
		if (pPlayer->isInCombat())
		{
			pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
			pPlayer->CLOSE_GOSSIP_MENU();

			return true;
		}

		pPlayer->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Enchanting
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51313) == true)
				{
			    pCreature->MonsterWhisper("You already know Enchanting!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(51313) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    pCreature->MonsterWhisper("You already know two Professions!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 1)
				        {
				        pPlayer->learnSpellHighRank(51313); // Grand Master Skill
				        pPlayer->learnSpellHighRank(44635); // Ring - Assault
				        pPlayer->learnSpellHighRank(44636); // Ring - Spellpower 
				        pPlayer->learnSpellHighRank(59636); // Ring - Stamina
						pPlayer->MonsterWhisper("You have succesfully learned Enchanting!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 2)
				        {
				        pPlayer->learnSpellHighRank(51313); // Grand Master Skill
				        pPlayer->learnSpellHighRank(44645); // Ring - Assault
				        pPlayer->learnSpellHighRank(44636); // Ring - Spellpower 
				        pPlayer->learnSpellHighRank(59636); // Ring - Stamina
						pPlayer->MonsterWhisper("You have succesfully learned Enchanting!", pPlayer->GetGUID());
						}		
				    }
					break;
					
			case GOSSIP_ACTION_INFO_DEF + 2: // Ring Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(34054, 8);
				pPlayer->AddItem(34055, 1);
		}
        return true;
	}
};

void AddSc_Script_TEnchanting()
{
	new Trainer_Enchanting();
}