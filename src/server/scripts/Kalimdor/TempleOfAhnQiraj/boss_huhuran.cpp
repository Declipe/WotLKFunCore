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
SDName: Boss_Huhuran
SD%Complete: 100
SDComment:
SDCategory: Temple of Ahn'Qiraj
EndScriptData */

#include "ScriptPCH.h"

#define EMOTE_GENERIC_FRENZY_KILL   -1000001
#define EMOTE_GENERIC_BERSERK       -1000004

#define SPELL_FRENZY 26051
#define SPELL_BERSERK 26068
#define SPELL_POISONBOLT 26052
#define SPELL_NOXIOUSPOISON 26053
#define SPELL_WYVERNSTING 26180
#define SPELL_ACIDSPIT 26050

class boss_huhuran : public CreatureScript
{
public:
    boss_huhuran() : CreatureScript("boss_huhuran") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_huhuranAI (creature);
    }

    struct boss_huhuranAI : public ScriptedAI
    {
        boss_huhuranAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 Frenzy_Timer;
        uint32 Wyvern_Timer;
        uint32 Spit_Timer;
        uint32 PoisonBolt_Timer;
        uint32 NoxiousPoison_Timer;
        uint32 FrenzyBack_Timer;

        bool Frenzy;
        bool Berserk;

        void Reset()
        {
            Frenzy_Timer = urand(25000, 35000);
            Wyvern_Timer = urand(18000, 28000);
            Spit_Timer = 8000;
            PoisonBolt_Timer = 4000;
            NoxiousPoison_Timer = urand(10000, 20000);
            FrenzyBack_Timer = 15000;

            Frenzy = false;
            Berserk = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            //Frenzy_Timer
            if (!Frenzy && Frenzy_Timer <= diff)
            {
                DoCast(me, SPELL_FRENZY);
                DoScriptText(EMOTE_GENERIC_FRENZY_KILL, me);
                Frenzy = true;
                PoisonBolt_Timer = 3000;
                Frenzy_Timer = urand(25000, 35000);
            } else Frenzy_Timer -= diff;

            // Wyvern Timer
            if (Wyvern_Timer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_WYVERNSTING);
                Wyvern_Timer = urand(15000, 32000);
            } else Wyvern_Timer -= diff;

            //Spit Timer
            if (Spit_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_ACIDSPIT);
                Spit_Timer = urand(5000, 10000);
            } else Spit_Timer -= diff;

            //NoxiousPoison_Timer
            if (NoxiousPoison_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_NOXIOUSPOISON);
                NoxiousPoison_Timer = urand(12000, 24000);
            } else NoxiousPoison_Timer -= diff;

            //PoisonBolt only if frenzy or berserk
            if (Frenzy || Berserk)
            {
                if (PoisonBolt_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_POISONBOLT);
                    PoisonBolt_Timer = 3000;
                } else PoisonBolt_Timer -= diff;
            }

            //FrenzyBack_Timer
            if (Frenzy && FrenzyBack_Timer <= diff)
            {
                me->InterruptNonMeleeSpells(false);
                Frenzy = false;
                FrenzyBack_Timer = 15000;
            } else FrenzyBack_Timer -= diff;

            if (!Berserk && HealthBelowPct(31))
            {
                me->InterruptNonMeleeSpells(false);
                DoScriptText(EMOTE_GENERIC_BERSERK, me);
                DoCast(me, SPELL_BERSERK);
                Berserk = true;
            }

            DoMeleeAttackIfReady();
        }
    };

};

void AddSC_boss_huhuran()
{
    new boss_huhuran();
}
