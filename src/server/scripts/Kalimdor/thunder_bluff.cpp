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
SDName: Thunder_Bluff
SD%Complete: 100
SDComment: Quest support: 925
SDCategory: Thunder Bluff
EndScriptData */

#include "ScriptPCH.h"

/*#####
# npc_cairne_bloodhoof
######*/

#define SPELL_BERSERKER_CHARGE  16636
#define SPELL_CLEAVE            16044
#define SPELL_MORTAL_STRIKE     16856
#define SPELL_THUNDERCLAP       23931
#define SPELL_UPPERCUT          22916

#define GOSSIP_HCB "I know this is rather silly but a young ward who is a bit shy would like your hoofprint."
//TODO: verify abilities/timers
class npc_cairne_bloodhoof : public CreatureScript
{
public:
    npc_cairne_bloodhoof() : CreatureScript("npc_cairne_bloodhoof") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_SENDER_INFO)
        {
            player->CastSpell(player, 23123, false);
            player->SEND_GOSSIP_MENU(7014, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(925) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HCB, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INFO);

        player->SEND_GOSSIP_MENU(7013, creature->GetGUID());

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cairne_bloodhoofAI (creature);
    }

    struct npc_cairne_bloodhoofAI : public ScriptedAI
    {
        npc_cairne_bloodhoofAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 BerserkerCharge_Timer;
        uint32 Cleave_Timer;
        uint32 MortalStrike_Timer;
        uint32 Thunderclap_Timer;
        uint32 Uppercut_Timer;

        void Reset()
        {
            BerserkerCharge_Timer = 30000;
            Cleave_Timer = 5000;
            MortalStrike_Timer = 10000;
            Thunderclap_Timer = 15000;
            Uppercut_Timer = 10000;
        }

        void EnterCombat(Unit* /*who*/) {}

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (BerserkerCharge_Timer <= diff)
            {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                if (target)
                    DoCast(target, SPELL_BERSERKER_CHARGE);
                BerserkerCharge_Timer = 25000;
            } else BerserkerCharge_Timer -= diff;

            if (Uppercut_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_UPPERCUT);
                Uppercut_Timer = 20000;
            } else Uppercut_Timer -= diff;

            if (Thunderclap_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_THUNDERCLAP);
                Thunderclap_Timer = 15000;
            } else Thunderclap_Timer -= diff;

            if (MortalStrike_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_MORTAL_STRIKE);
                MortalStrike_Timer = 15000;
            } else MortalStrike_Timer -= diff;

            if (Cleave_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_CLEAVE);
                Cleave_Timer = 7000;
            } else Cleave_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };

};

void AddSC_thunder_bluff()
{
    new npc_cairne_bloodhoof();
}
