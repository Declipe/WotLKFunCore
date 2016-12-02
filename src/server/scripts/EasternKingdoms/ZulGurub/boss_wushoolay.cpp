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
SDName: Boss_Wushoolay
SD%Complete: 100
SDComment:
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptPCH.h"
#include "zulgurub.h"

#define SPELL_LIGHTNINGCLOUD         25033
#define SPELL_LIGHTNINGWAVE          24819

class boss_wushoolay : public CreatureScript
{
    public:

        boss_wushoolay()
            : CreatureScript("boss_wushoolay")
        {
        }

        struct boss_wushoolayAI : public ScriptedAI
        {
            boss_wushoolayAI(Creature* creature) : ScriptedAI(creature) {}

            uint32 LightningCloud_Timer;
            uint32 LightningWave_Timer;

            void Reset()
            {
                LightningCloud_Timer = urand(5000, 10000);
                LightningWave_Timer = urand(8000, 16000);
            }

            void EnterCombat(Unit* /*who*/)
            {
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                //LightningCloud_Timer
                if (LightningCloud_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_LIGHTNINGCLOUD);
                    LightningCloud_Timer = urand(15000, 20000);
                } else LightningCloud_Timer -= diff;

                //LightningWave_Timer
                if (LightningWave_Timer <= diff)
                {
                    Unit* target = NULL;
                    target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if (target) DoCast(target, SPELL_LIGHTNINGWAVE);

                    LightningWave_Timer = urand(12000, 16000);
                } else LightningWave_Timer -= diff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_wushoolayAI(creature);
        }
};

void AddSC_boss_wushoolay()
{
    new boss_wushoolay();
}

