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
SDName: Boss_Ebonroc
SD%Complete: 50
SDComment: Shadow of Ebonroc needs core support
SDCategory: Blackwing Lair
EndScriptData */

#include "ScriptPCH.h"

#define SPELL_SHADOWFLAME           22539
#define SPELL_WINGBUFFET            18500
#define SPELL_SHADOWOFEBONROC       23340
#define SPELL_HEAL                  41386                   //Thea Heal spell of his Shadow

class boss_ebonroc : public CreatureScript
{
public:
    boss_ebonroc() : CreatureScript("boss_ebonroc") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ebonrocAI (creature);
    }

    struct boss_ebonrocAI : public ScriptedAI
    {
        boss_ebonrocAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 ShadowFlame_Timer;
        uint32 WingBuffet_Timer;
        uint32 ShadowOfEbonroc_Timer;
        uint32 Heal_Timer;

        void Reset()
        {
            ShadowFlame_Timer = 15000;                          //These times are probably wrong
            WingBuffet_Timer = 30000;
            ShadowOfEbonroc_Timer = 45000;
            Heal_Timer = 1000;
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoZoneInCombat();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            //Shadowflame Timer
            if (ShadowFlame_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOWFLAME);
                ShadowFlame_Timer = urand(12000, 15000);
            } else ShadowFlame_Timer -= diff;

            //Wing Buffet Timer
            if (WingBuffet_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_WINGBUFFET);
                WingBuffet_Timer = 25000;
            } else WingBuffet_Timer -= diff;

            //Shadow of Ebonroc Timer
            if (ShadowOfEbonroc_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOWOFEBONROC);
                ShadowOfEbonroc_Timer = urand(25000, 350000);
            } else ShadowOfEbonroc_Timer -= diff;

            if (me->getVictim()->HasAura(SPELL_SHADOWOFEBONROC))
            {
                if (Heal_Timer <= diff)
                {
                    DoCast(me, SPELL_HEAL);
                    Heal_Timer = urand(1000, 3000);
                } else Heal_Timer -= diff;
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_ebonroc()
{
    new boss_ebonroc();
}
