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

#include "ScriptPCH.h"

enum Spells
{
    SPELL_WHIRLWIND                                        = 15589,
    SPELL_MORTALSTRIKE                                     = 24573
};

class boss_gorosh_the_dervish : public CreatureScript
{
public:
    boss_gorosh_the_dervish() : CreatureScript("boss_gorosh_the_dervish") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_gorosh_the_dervishAI (creature);
    }

    struct boss_gorosh_the_dervishAI : public ScriptedAI
    {
        boss_gorosh_the_dervishAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 WhirlWind_Timer;
        uint32 MortalStrike_Timer;

        void Reset()
        {
            WhirlWind_Timer = 12000;
            MortalStrike_Timer = 22000;
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            //WhirlWind_Timer
            if (WhirlWind_Timer <= diff)
            {
                DoCast(me, SPELL_WHIRLWIND);
                WhirlWind_Timer = 15000;
            } else WhirlWind_Timer -= diff;

            //MortalStrike_Timer
            if (MortalStrike_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_MORTALSTRIKE);
                MortalStrike_Timer = 15000;
            } else MortalStrike_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_gorosh_the_dervish()
{
    new boss_gorosh_the_dervish();
}
