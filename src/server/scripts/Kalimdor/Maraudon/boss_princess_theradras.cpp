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
SDName: Boss_Princess_Theradras
SD%Complete: 100
SDComment:
SDCategory: Maraudon
EndScriptData */

#include "ScriptPCH.h"

enum Spells
{
    SPELL_DUSTFIELD             = 21909,
    SPELL_BOULDER               = 21832,
    SPELL_THRASH                = 3391,
    SPELL_REPULSIVEGAZE         = 21869
};

class boss_princess_theradras : public CreatureScript
{
public:
    boss_princess_theradras() : CreatureScript("boss_princess_theradras") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ptheradrasAI (creature);
    }

    struct boss_ptheradrasAI : public ScriptedAI
    {
        boss_ptheradrasAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 Dustfield_Timer;
        uint32 Boulder_Timer;
        uint32 Thrash_Timer;
        uint32 RepulsiveGaze_Timer;

        void Reset()
        {
            Dustfield_Timer = 8000;
            Boulder_Timer = 2000;
            Thrash_Timer = 5000;
            RepulsiveGaze_Timer = 23000;
        }

        void EnterCombat(Unit* /*who*/) {}

        void JustDied(Unit* /*killer*/)
        {
            me->SummonCreature(12238, 28.067f, 61.875f, -123.405f, 4.67f, TEMPSUMMON_TIMED_DESPAWN, 600000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            //Dustfield_Timer
            if (Dustfield_Timer <= diff)
            {
                DoCast(me, SPELL_DUSTFIELD);
                Dustfield_Timer = 14000;
            }
            else Dustfield_Timer -= diff;

            //Boulder_Timer
            if (Boulder_Timer <= diff)
            {
                Unit* target = NULL;
                target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                if (target)
                    DoCast(target, SPELL_BOULDER);
                Boulder_Timer = 10000;
            }
            else Boulder_Timer -= diff;

            //RepulsiveGaze_Timer
            if (RepulsiveGaze_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_REPULSIVEGAZE);
                RepulsiveGaze_Timer = 20000;
            }
            else RepulsiveGaze_Timer -= diff;

            //Thrash_Timer
            if (Thrash_Timer <= diff)
            {
                DoCast(me, SPELL_THRASH);
                Thrash_Timer = 18000;
            }
            else Thrash_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_ptheradras()
{
    new boss_princess_theradras();
}
