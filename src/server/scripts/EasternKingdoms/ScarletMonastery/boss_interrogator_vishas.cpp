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
SDName: Boss_Interrogator_Vishas
SD%Complete: 100
SDComment:
SDCategory: Scarlet Monastery
EndScriptData */

#include "ScriptPCH.h"
#include "scarlet_monastery.h"

enum Says
{
    SAY_AGGRO               = -1189011,
    SAY_HEALTH1             = -1189012,
    SAY_HEALTH2             = -1189013,
    SAY_KILL                = -1189014,
    SAY_TRIGGER_VORREL      = -1189015
};

enum Spells
{
    SPELL_SHADOWWORDPAIN    = 2767
};

class boss_interrogator_vishas : public CreatureScript
{
public:
    boss_interrogator_vishas() : CreatureScript("boss_interrogator_vishas") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_interrogator_vishasAI (creature);
    }

    struct boss_interrogator_vishasAI : public ScriptedAI
    {
        boss_interrogator_vishasAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;

        bool Yell30;
        bool Yell60;
        uint32 ShadowWordPain_Timer;

        void Reset()
        {
            ShadowWordPain_Timer = 5000;
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);
        }

        void KilledUnit(Unit* /*Victim*/)
        {
            DoScriptText(SAY_KILL, me);
        }

        void JustDied(Unit* /*killer*/)
        {
            if (!instance)
                return;

            //Any other Actions to do with vorrel? setStandState?
            if (Unit* vorrel = Unit::GetUnit(*me, instance->GetData64(DATA_VORREL)))
                DoScriptText(SAY_TRIGGER_VORREL, vorrel);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            //If we are low on hp Do sayings
            if (!Yell60 && !HealthAbovePct(60))
            {
                DoScriptText(SAY_HEALTH1, me);
                Yell60 = true;
            }

            if (!Yell30 && !HealthAbovePct(30))
            {
                DoScriptText(SAY_HEALTH2, me);
                Yell30 = true;
            }

            //ShadowWordPain_Timer
            if (ShadowWordPain_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOWWORDPAIN);
                ShadowWordPain_Timer = urand(5000, 15000);
            }
            else ShadowWordPain_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_interrogator_vishas()
{
    new boss_interrogator_vishas();
}
