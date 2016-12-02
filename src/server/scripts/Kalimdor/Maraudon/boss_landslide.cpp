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
SDName: Boss_Landslide
SD%Complete: 100
SDComment:
SDCategory: Maraudon
EndScriptData */

#include "ScriptPCH.h"

enum Spells
{
    SPELL_KNOCKAWAY         = 18670,
    SPELL_TRAMPLE           = 5568,
    SPELL_LANDSLIDE         = 21808
};

class boss_landslide : public CreatureScript
{
public:
    boss_landslide() : CreatureScript("boss_landslide") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_landslideAI (creature);
    }

    struct boss_landslideAI : public ScriptedAI
    {
        boss_landslideAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 KnockAway_Timer;
        uint32 Trample_Timer;
        uint32 Landslide_Timer;

        void Reset()
        {
            KnockAway_Timer = 8000;
            Trample_Timer = 2000;
            Landslide_Timer = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            //KnockAway_Timer
            if (KnockAway_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_KNOCKAWAY);
                KnockAway_Timer = 15000;
            }
            else KnockAway_Timer -= diff;

            //Trample_Timer
            if (Trample_Timer <= diff)
            {
                DoCast(me, SPELL_TRAMPLE);
                Trample_Timer = 8000;
            }
            else Trample_Timer -= diff;

            //Landslide
            if (HealthBelowPct(50))
            {
                if (Landslide_Timer <= diff)
                {
                    me->InterruptNonMeleeSpells(false);
                    DoCast(me, SPELL_LANDSLIDE);
                    Landslide_Timer = 60000;
                }
                else Landslide_Timer -= diff;
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_landslide()
{
    new boss_landslide();
}
