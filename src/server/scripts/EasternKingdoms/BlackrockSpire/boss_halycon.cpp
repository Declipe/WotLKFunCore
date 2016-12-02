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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "blackrock_spire.h"

enum Spells
{
    SPELL_CROWDPUMMEL               = 10887,
    SPELL_MIGHTYBLOW                = 14099,
};

enum Events
{
    EVENT_CROWD_PUMMEL              = 1,
    EVENT_MIGHTY_BLOW               = 2,
};

const Position SummonLocation = { -169.839f, -324.961f, 64.401f, 3.124f };

class boss_halycon : public CreatureScript
{
public:
    boss_halycon() : CreatureScript("boss_halycon") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_halyconAI(creature);
    }

    struct boss_halyconAI : public BossAI
    {
        boss_halyconAI(Creature* creature) : BossAI(creature, DATA_HALYCON) {}

        bool Summoned;

        void Reset()
        {
            _Reset();
            Summoned = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            events.ScheduleEvent(EVENT_CROWD_PUMMEL, 8 * IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_MIGHTY_BLOW, 14 * IN_MILLISECONDS);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
        }

        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            //Summon Gizrul
            if (!Summoned && HealthBelowPct(25))
            {
                me->SummonCreature(NPC_GIZRUL_THE_SLAVENER, SummonLocation, TEMPSUMMON_TIMED_DESPAWN, 300 * IN_MILLISECONDS);
                Summoned = true;
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CROWD_PUMMEL:
                        DoCast(me->getVictim(), SPELL_CROWDPUMMEL);
                        events.ScheduleEvent(EVENT_CROWD_PUMMEL, 14 * IN_MILLISECONDS);
                        break;
                    case EVENT_MIGHTY_BLOW:
                        DoCast(me->getVictim(), SPELL_MIGHTYBLOW);
                        events.ScheduleEvent(EVENT_MIGHTY_BLOW, 10 * IN_MILLISECONDS);
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };

};

void AddSC_boss_halycon()
{
    new boss_halycon();
}
