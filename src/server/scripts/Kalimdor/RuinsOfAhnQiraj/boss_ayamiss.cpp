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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ruins_of_ahnqiraj.h"

enum eAyamiss
{
    SPELL_STINGERSPRAY          =  25749,
    SPELL_POISONSTINGER         =  25748,                          //only used in phase1
    SPELL_PARALYZE              =  25725,
    SPELL_TRASH                 =  3391,
    SPELL_FRENZY                =  8269,
    SPELL_LASH                  =  25852,

    EMOTE_FRENZY                =  -1000002,

    SPELL_FEED                  =  25721,
};

class boss_ayamiss : public CreatureScript
{
    public:
        boss_ayamiss() : CreatureScript("boss_ayamiss") { }

        struct boss_ayamissAI : public ScriptedAI
        {
            boss_ayamissAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            uint32 STINGERSPRAY_Timer;
            uint32 POISONSTINGER_Timer;
            uint32 SUMMONSWARMER_Timer;
            uint32 phase;

            InstanceScript* instance;

            void Reset()
            {
                STINGERSPRAY_Timer = 30000;
                POISONSTINGER_Timer = 30000;
                SUMMONSWARMER_Timer = 60000;
                phase = 1;

            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                //If he is 70% start phase 2
                if (phase == 1 && !HealthAbovePct(70) && !me->IsNonMeleeSpellCasted(false))
                {
                    phase=2;
                }

                //STINGERSPRAY_Timer (only in phase2)
                if (phase == 2 && STINGERSPRAY_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_STINGERSPRAY);
                    STINGERSPRAY_Timer = 30000;
                } else STINGERSPRAY_Timer -= diff;

                //POISONSTINGER_Timer (only in phase1)
                if (phase == 1 && POISONSTINGER_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_POISONSTINGER);
                    POISONSTINGER_Timer = 30000;
                } else POISONSTINGER_Timer -= diff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_ayamissAI (creature);
        }
};

void AddSC_boss_ayamiss()
{
    new boss_ayamiss();
}
