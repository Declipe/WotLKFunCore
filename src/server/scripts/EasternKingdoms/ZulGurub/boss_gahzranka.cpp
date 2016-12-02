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
SDName: Boss_Gahz'ranka
SD%Complete: 85
SDComment: Massive Geyser with knockback not working. Spell buggy.
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptPCH.h"

#define SPELL_FROSTBREATH            16099
#define SPELL_MASSIVEGEYSER          22421                  //Not working. Cause its a summon...
#define SPELL_SLAM                   24326

class boss_gahzranka : public CreatureScript
{
    public:
        boss_gahzranka() : CreatureScript("boss_gahzranka") { }

        struct boss_gahzrankaAI : public ScriptedAI
        {
            boss_gahzrankaAI(Creature* creature) : ScriptedAI(creature) { }
            uint32 Frostbreath_Timer;
            uint32 MassiveGeyser_Timer;
            uint32 Slam_Timer;

            void Reset()
            {
                Frostbreath_Timer = 8000;
                MassiveGeyser_Timer = 25000;
                Slam_Timer = 17000;
            }

            void EnterCombat(Unit* /*who*/)
            {
            }

            void UpdateAI(const uint32 diff)
            {
                //Return since we have no target
                if (!UpdateVictim())
                    return;

                //Frostbreath_Timer
                if (Frostbreath_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_FROSTBREATH);
                    Frostbreath_Timer = urand(7000, 11000);
                } else Frostbreath_Timer -= diff;

                //MassiveGeyser_Timer
                if (MassiveGeyser_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_MASSIVEGEYSER);
                    DoResetThreat();

                    MassiveGeyser_Timer = urand(22000, 32000);
                } else MassiveGeyser_Timer -= diff;

                //Slam_Timer
                if (Slam_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_SLAM);
                    Slam_Timer = urand(12000, 20000);
                } else Slam_Timer -= diff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_gahzrankaAI(creature);
        }
};

void AddSC_boss_gahzranka()
{
    new boss_gahzranka();
}

