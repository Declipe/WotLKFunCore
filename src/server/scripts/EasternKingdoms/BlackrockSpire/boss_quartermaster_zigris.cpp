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
    SPELL_SHOOT                     = 16496,
    SPELL_STUNBOMB                  = 16497,
    SPELL_HEALING_POTION            = 15504,
    SPELL_HOOKEDNET                 = 15609,
};

enum Events
{
    EVENT_SHOOT                     = 1,
    EVENT_STUN_BOMB                 = 2,
};

class quartermaster_zigris : public CreatureScript
{
public:
    quartermaster_zigris() : CreatureScript("quartermaster_zigris") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_quatermasterzigrisAI(creature);
    }

    struct boss_quatermasterzigrisAI : public BossAI
    {
        boss_quatermasterzigrisAI(Creature* creature) : BossAI(creature, DATA_QUARTERMASTER_ZIGRIS) {}

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            events.ScheduleEvent(EVENT_SHOOT,      1 * IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_STUN_BOMB, 16 * IN_MILLISECONDS);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
        }

        void UpdateAI(uint32 const diff)
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
                    case EVENT_SHOOT:
                        DoCast(me->getVictim(), SPELL_SHOOT);
                        events.ScheduleEvent(EVENT_SHOOT, 500);
                        break;
                    case EVENT_STUN_BOMB:
                        DoCast(me->getVictim(), SPELL_STUNBOMB);
                        events.ScheduleEvent(EVENT_STUN_BOMB, 14 * IN_MILLISECONDS);
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_quatermasterzigris()
{
    new quartermaster_zigris();
}
