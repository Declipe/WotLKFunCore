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
SDName: Boss_Firemaw
SD%Complete: 100
SDComment:
SDCategory: Blackwing Lair
EndScriptData */

#include "ScriptPCH.h"

#define SPELL_SHADOWFLAME       22539
#define SPELL_WINGBUFFET        23339
#define SPELL_FLAMEBUFFET       23341

class boss_firemaw : public CreatureScript
{
public:
    boss_firemaw() : CreatureScript("boss_firemaw") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_firemawAI (creature);
    }

    struct boss_firemawAI : public ScriptedAI
    {
        boss_firemawAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 ShadowFlame_Timer;
        uint32 WingBuffet_Timer;
        uint32 FlameBuffet_Timer;

        void Reset()
        {
            ShadowFlame_Timer = 30000;                          //These times are probably wrong
            WingBuffet_Timer = 24000;
            FlameBuffet_Timer = 5000;
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoZoneInCombat();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            //ShadowFlame_Timer
            if (ShadowFlame_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOWFLAME);
                ShadowFlame_Timer = urand(15000, 18000);
            } else ShadowFlame_Timer -= diff;

            //WingBuffet_Timer
            if (WingBuffet_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_WINGBUFFET);
                if (DoGetThreat(me->getVictim()))
                    DoModifyThreatPercent(me->getVictim(), -75);

                WingBuffet_Timer = 25000;
            } else WingBuffet_Timer -= diff;

            //FlameBuffet_Timer
            if (FlameBuffet_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_FLAMEBUFFET);
                FlameBuffet_Timer = 5000;
            } else FlameBuffet_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_firemaw()
{
    new boss_firemaw();
}
