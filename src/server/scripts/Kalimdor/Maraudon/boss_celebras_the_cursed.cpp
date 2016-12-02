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
SDName: Boss_Celebras_the_Cursed
SD%Complete: 100
SDComment:
SDCategory: Maraudon
EndScriptData */

#include "ScriptPCH.h"

enum Spells
{
    SPELL_WRATH                 = 21807,
    SPELL_ENTANGLINGROOTS       = 12747,
    SPELL_CORRUPT_FORCES        = 21968
};

class celebras_the_cursed : public CreatureScript
{
public:
    celebras_the_cursed() : CreatureScript("celebras_the_cursed") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new celebras_the_cursedAI (creature);
    }

    struct celebras_the_cursedAI : public ScriptedAI
    {
        celebras_the_cursedAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 Wrath_Timer;
        uint32 EntanglingRoots_Timer;
        uint32 CorruptForces_Timer;

        void Reset()
        {
            Wrath_Timer = 8000;
            EntanglingRoots_Timer = 2000;
            CorruptForces_Timer = 30000;
        }

        void EnterCombat(Unit* /*who*/) { }

        void JustDied(Unit* /*killer*/)
        {
            me->SummonCreature(13716, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 600000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            //Wrath
            if (Wrath_Timer <= diff)
            {
                Unit* target = NULL;
                target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                if (target)
                    DoCast(target, SPELL_WRATH);
                Wrath_Timer = 8000;
            }
            else Wrath_Timer -= diff;

            //EntanglingRoots
            if (EntanglingRoots_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_ENTANGLINGROOTS);
                EntanglingRoots_Timer = 20000;
            }
            else EntanglingRoots_Timer -= diff;

            //CorruptForces
            if (CorruptForces_Timer <= diff)
            {
                me->InterruptNonMeleeSpells(false);
                DoCast(me, SPELL_CORRUPT_FORCES);
                CorruptForces_Timer = 20000;
            }
            else CorruptForces_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_celebras_the_cursed()
{
    new celebras_the_cursed();
}
