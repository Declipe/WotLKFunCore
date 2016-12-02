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
SDName: Boss_Grilek
SD%Complete: 100
SDComment:
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptPCH.h"
#include "zulgurub.h"

#define SPELL_AVARTAR                24646                  //The Enrage Spell
#define SPELL_GROUNDTREMOR            6524

class boss_grilek : public CreatureScript
{
    public:
        boss_grilek() : CreatureScript("boss_grilek") { }

        struct boss_grilekAI : public ScriptedAI
        {
            boss_grilekAI(Creature* creature) : ScriptedAI(creature) { }

            uint32 Avartar_Timer;
            uint32 GroundTremor_Timer;

            void Reset()
            {
                Avartar_Timer = urand(15000, 25000);
                GroundTremor_Timer = urand(8000, 16000);
            }

            void EnterCombat(Unit* /*who*/)
            {
            }

            void UpdateAI(const uint32 diff)
            {
                //Return since we have no target
                if (!UpdateVictim())
                    return;

                //Avartar_Timer
                if (Avartar_Timer <= diff)
                {

                    DoCast(me, SPELL_AVARTAR);
                    Unit* target = NULL;

                    target = SelectTarget(SELECT_TARGET_RANDOM, 1);

                    if (DoGetThreat(me->getVictim()))
                        DoModifyThreatPercent(me->getVictim(), -50);
                    if (target)
                        AttackStart(target);

                    Avartar_Timer = urand(25000, 35000);
                } else Avartar_Timer -= diff;

                //GroundTremor_Timer
                if (GroundTremor_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_GROUNDTREMOR);
                    GroundTremor_Timer = urand(12000, 16000);
                } else GroundTremor_Timer -= diff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_grilekAI(creature);
        }
};

void AddSC_boss_grilek()
{
    new boss_grilek();
}

