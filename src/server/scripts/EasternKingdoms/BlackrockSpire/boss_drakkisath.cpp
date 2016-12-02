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
    SPELL_FIRENOVA                  = 23462,
    SPELL_CLEAVE                    = 20691,
    SPELL_CONFLIGURATION            = 16805,
    SPELL_THUNDERCLAP               = 15548, //Not sure if right ID. 23931 would be a harder possibility.
};

enum Events
{
    EVENT_FIRE_NOVA                = 1,
    EVENT_CLEAVE                   = 2,
    EVENT_CONFLIGURATION           = 3,
    EVENT_THUNDERCLAP              = 4,
};

class boss_drakkisath : public CreatureScript
{
public:
    boss_drakkisath() : CreatureScript("boss_drakkisath") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_drakkisathAI(creature);
    }

    struct boss_drakkisathAI : public BossAI
    {
        boss_drakkisathAI(Creature* creature) : BossAI(creature, DATA_GENERAL_DRAKKISATH) {}

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            events.ScheduleEvent(EVENT_FIRE_NOVA, 6 * IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_CLEAVE,    8 * IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_CONFLIGURATION, 15 * IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_THUNDERCLAP,    17 * IN_MILLISECONDS);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FIRE_NOVA:
                        DoCast(me->getVictim(), SPELL_FIRENOVA);
                        events.ScheduleEvent(EVENT_FIRE_NOVA, 10 * IN_MILLISECONDS);
                        break;
                    case EVENT_CLEAVE:
                        DoCast(me->getVictim(), SPELL_CLEAVE);
                        events.ScheduleEvent(EVENT_CLEAVE, 8 * IN_MILLISECONDS);
                        break;
                    case EVENT_CONFLIGURATION:
                        DoCast(me->getVictim(), SPELL_CONFLIGURATION);
                        events.ScheduleEvent(EVENT_CONFLIGURATION, 18 * IN_MILLISECONDS);
                        break;
                    case EVENT_THUNDERCLAP:
                        DoCast(me->getVictim(), SPELL_THUNDERCLAP);
                        events.ScheduleEvent(EVENT_THUNDERCLAP, 20 * IN_MILLISECONDS);
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_drakkisath()
{
    new boss_drakkisath();
}
