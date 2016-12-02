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
    SPELL_SHADOWBOLT                                       = 17228,
    SPELL_CURSEOFTONGUES                                   = 15470,
    SPELL_CURSEOFWEAKNESS                                  = 17227,
    SPELL_DEMONARMOR                                       = 11735,
    SPELL_ENVELOPINGWEB                                    = 15471
};

class boss_anubshiah : public CreatureScript
{
public:
    boss_anubshiah() : CreatureScript("boss_anubshiah") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_anubshiahAI (creature);
    }

    struct boss_anubshiahAI : public ScriptedAI
    {
        boss_anubshiahAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 ShadowBolt_Timer;
        uint32 CurseOfTongues_Timer;
        uint32 CurseOfWeakness_Timer;
        uint32 DemonArmor_Timer;
        uint32 EnvelopingWeb_Timer;

        void Reset()
        {
            ShadowBolt_Timer = 7000;
            CurseOfTongues_Timer = 24000;
            CurseOfWeakness_Timer = 12000;
            DemonArmor_Timer = 3000;
            EnvelopingWeb_Timer = 16000;
        }

        void EnterCombat(Unit* /*who*/) {}

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            //ShadowBolt_Timer
            if (ShadowBolt_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOWBOLT);
                ShadowBolt_Timer = 7000;
            } else ShadowBolt_Timer -= diff;

            //CurseOfTongues_Timer
            if (CurseOfTongues_Timer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(target, SPELL_CURSEOFTONGUES);
                CurseOfTongues_Timer = 18000;
            } else CurseOfTongues_Timer -= diff;

            //CurseOfWeakness_Timer
            if (CurseOfWeakness_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_CURSEOFWEAKNESS);
                CurseOfWeakness_Timer = 45000;
            } else CurseOfWeakness_Timer -= diff;

            //DemonArmor_Timer
            if (DemonArmor_Timer <= diff)
            {
                DoCast(me, SPELL_DEMONARMOR);
                DemonArmor_Timer = 300000;
            } else DemonArmor_Timer -= diff;

            //EnvelopingWeb_Timer
            if (EnvelopingWeb_Timer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(target, SPELL_ENVELOPINGWEB);
                EnvelopingWeb_Timer = 12000;
            } else EnvelopingWeb_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_anubshiah()
{
    new boss_anubshiah();
}
