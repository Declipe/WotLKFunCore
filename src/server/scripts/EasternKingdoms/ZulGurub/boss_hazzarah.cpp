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
SDName: Boss_Hazzarah
SD%Complete: 100
SDComment:
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptPCH.h"
#include "zulgurub.h"

#define SPELL_MANABURN         26046
#define SPELL_SLEEP            24664

class boss_hazzarah : public CreatureScript
{
    public:

        boss_hazzarah()
            : CreatureScript("boss_hazzarah")
        {
        }

        struct boss_hazzarahAI : public ScriptedAI
        {
            boss_hazzarahAI(Creature* creature) : ScriptedAI(creature) {}

            uint32 ManaBurn_Timer;
            uint32 Sleep_Timer;
            uint32 Illusions_Timer;

            void Reset()
            {
                ManaBurn_Timer = urand(4000, 10000);
                Sleep_Timer = urand(10000, 18000);
                Illusions_Timer = urand(10000, 18000);
            }

            void EnterCombat(Unit* /*who*/)
            {
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                //ManaBurn_Timer
                if (ManaBurn_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_MANABURN);
                    ManaBurn_Timer = urand(8000, 16000);
                } else ManaBurn_Timer -= diff;

                //Sleep_Timer
                if (Sleep_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_SLEEP);
                    Sleep_Timer = urand(12000, 20000);
                } else Sleep_Timer -= diff;

                //Illusions_Timer
                if (Illusions_Timer <= diff)
                {
                    //We will summon 3 illusions that will spawn on a random gamer and attack this gamer
                    //We will just use one model for the beginning
                    Unit* target = NULL;
                    for (uint8 i = 0; i < 3; ++i)
                    {
                        target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                        if (!target)
                            return;

                        Creature* Illusion = me->SummonCreature(15163, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000);
                        if (Illusion)
                            Illusion->AI()->AttackStart(target);
                    }

                    Illusions_Timer = urand(15000, 25000);
                } else Illusions_Timer -= diff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_hazzarahAI(creature);
        }
};

void AddSC_boss_hazzarah()
{
    new boss_hazzarah();
}

