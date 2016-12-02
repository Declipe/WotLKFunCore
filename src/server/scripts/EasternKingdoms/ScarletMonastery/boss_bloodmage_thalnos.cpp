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
SDName: Boss_Bloodmage_Thalnos
SD%Complete: 100
SDComment:
SDCategory: Scarlet Monastery
EndScriptData */

#include "ScriptPCH.h"

enum eEnums
{
    SAY_AGGRO               = -1189016,
    SAY_HEALTH              = -1189017,
    SAY_KILL                = -1189018,

    SPELL_FLAMESHOCK        = 8053,
    SPELL_SHADOWBOLT        = 1106,
    SPELL_FLAMESPIKE        = 8814,
    SPELL_FIRENOVA          = 16079,
};

class boss_bloodmage_thalnos : public CreatureScript
{
public:
    boss_bloodmage_thalnos() : CreatureScript("boss_bloodmage_thalnos") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_bloodmage_thalnosAI (creature);
    }

    struct boss_bloodmage_thalnosAI : public ScriptedAI
    {
        boss_bloodmage_thalnosAI(Creature* creature) : ScriptedAI(creature) {}

        bool HpYell;
        uint32 FlameShock_Timer;
        uint32 ShadowBolt_Timer;
        uint32 FlameSpike_Timer;
        uint32 FireNova_Timer;

        void Reset()
        {
            HpYell = false;
            FlameShock_Timer = 10000;
            ShadowBolt_Timer = 2000;
            FlameSpike_Timer = 8000;
            FireNova_Timer = 40000;
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);
        }

        void KilledUnit(Unit* /*Victim*/)
        {
            DoScriptText(SAY_KILL, me);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            //If we are <35% hp
            if (!HpYell && !HealthAbovePct(35))
            {
                DoScriptText(SAY_HEALTH, me);
                HpYell = true;
            }

            //FlameShock_Timer
            if (FlameShock_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_FLAMESHOCK);
                FlameShock_Timer = urand(10000, 15000);
            }
            else FlameShock_Timer -= diff;

            //FlameSpike_Timer
            if (FlameSpike_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_FLAMESPIKE);
                FlameSpike_Timer = 30000;
            }
            else FlameSpike_Timer -= diff;

            //FireNova_Timer
            if (FireNova_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_FIRENOVA);
                FireNova_Timer = 40000;
            }
            else FireNova_Timer -= diff;

            //ShadowBolt_Timer
            if (ShadowBolt_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOWBOLT);
                ShadowBolt_Timer = 2000;
            }
            else ShadowBolt_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_bloodmage_thalnos()
{
    new boss_bloodmage_thalnos();
}
