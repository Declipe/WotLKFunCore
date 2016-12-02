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
SDName: boss_timmy_the_cruel
SD%Complete: 100
SDComment:
SDCategory: Stratholme
EndScriptData */

#include "ScriptPCH.h"

#define SAY_SPAWN   "TIMMY!"

#define SPELL_RAVENOUSCLAW    17470

class boss_timmy_the_cruel : public CreatureScript
{
public:
    boss_timmy_the_cruel() : CreatureScript("boss_timmy_the_cruel") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_timmy_the_cruelAI (creature);
    }

    struct boss_timmy_the_cruelAI : public ScriptedAI
    {
        boss_timmy_the_cruelAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 RavenousClaw_Timer;
        bool HasYelled;

        void Reset()
        {
            RavenousClaw_Timer = 10000;
            HasYelled = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (!HasYelled)
            {
                me->MonsterYell(SAY_SPAWN, LANG_UNIVERSAL, 0);
                HasYelled = true;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            //RavenousClaw
            if (RavenousClaw_Timer <= diff)
            {
                //Cast
                DoCast(me->getVictim(), SPELL_RAVENOUSCLAW);
                //15 seconds until we should cast this again
                RavenousClaw_Timer = 15000;
            } else RavenousClaw_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };

};

void AddSC_boss_timmy_the_cruel()
{
    new boss_timmy_the_cruel();
}
