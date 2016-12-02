/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
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
#include "blackfathom_deeps.h"

enum Spells
{
    SPELL_POISON_CLOUD                                     = 3815,
    SPELL_FRENZIED_RAGE                                    = 3490
};

class boss_aku_mai : public CreatureScript
{
public:
    boss_aku_mai() : CreatureScript("boss_aku_mai") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_aku_maiAI (creature);
    }

    struct boss_aku_maiAI : public ScriptedAI
    {
        boss_aku_maiAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        uint32 poisonCloudTimer;
        bool bIsEnraged;

        InstanceScript* instance;

        void Reset()
        {
            poisonCloudTimer = urand(5000, 9000);
            bIsEnraged = false;
            if (instance)
                instance->SetData(TYPE_AKU_MAI, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (instance)
                instance->SetData(TYPE_AKU_MAI, IN_PROGRESS);
        }

        void JustDied(Unit* /*killer*/)
        {
            if (instance)
                instance->SetData(TYPE_AKU_MAI, DONE);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (poisonCloudTimer < diff)
            {
                DoCastVictim(SPELL_POISON_CLOUD);
                poisonCloudTimer = urand(25000, 50000);
            } else poisonCloudTimer -= diff;

            if (!bIsEnraged && HealthBelowPct(30))
            {
                DoCast(me, SPELL_FRENZIED_RAGE);
                bIsEnraged = true;
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_aku_mai()
{
    new boss_aku_mai();
}
