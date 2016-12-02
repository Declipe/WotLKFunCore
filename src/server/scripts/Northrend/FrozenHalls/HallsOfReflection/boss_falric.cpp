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
#include "halls_of_reflection.h"

enum Yells
{
    SAY_AGGRO                                     = -1668050,
    SAY_SLAY_1                                    = -1668051,
    SAY_SLAY_2                                    = -1668052,
    SAY_DEATH                                     = -1668053,
    SAY_IMPENDING_DESPAIR                         = -1668054,
    SAY_DEFILING_HORROR                           = -1668055,
};

enum Spells
{
    SPELL_QUIVERING_STRIKE                        = 72422,
    SPELL_IMPENDING_DESPAIR                       = 72426,
    SPELL_DEFILING_HORROR                         = 72435,
    SPELL_HOPELESSNESS                            = 72395,
    H_SPELL_HOPELESSNESS                          = 72390, // TODO: not in dbc. Add in DB.
};

enum Events
{
    EVENT_NONE,
    EVENT_QUIVERING_STRIKE,
    EVENT_IMPENDING_DESPAIR,
    EVENT_DEFILING_HORROR,
};

class boss_falric : public CreatureScript
{
public:
    boss_falric() : CreatureScript("boss_falric") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_falricAI(creature);
    }

    struct boss_falricAI : public boss_horAI
    {
        boss_falricAI(Creature* creature) : boss_horAI(creature) {}

        uint8 uiHopelessnessCount;

        void Reset()
        {
            boss_horAI::Reset();

            uiHopelessnessCount = 0;

            if (instance)
                instance->SetData(DATA_FALRIC_EVENT, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);
            if (instance)
                instance->SetData(DATA_FALRIC_EVENT, IN_PROGRESS);

            events.ScheduleEvent(EVENT_QUIVERING_STRIKE, 23000);
            events.ScheduleEvent(EVENT_IMPENDING_DESPAIR, 9000);
            events.ScheduleEvent(EVENT_DEFILING_HORROR, urand(25000, 45000)); // TODO adjust timer.
        }

        void JustDied(Unit* /*killer*/)
        {
            DoScriptText(SAY_DEATH, me);

            if (instance)
                instance->SetData(DATA_FALRIC_EVENT, DONE);
        }

        void KilledUnit(Unit* /*victim*/)
        {
            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2), me);
        }

        void UpdateAI(const uint32 diff)
        {
            // Return since we have no target
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
                case EVENT_QUIVERING_STRIKE:
                    DoCast(SPELL_QUIVERING_STRIKE);
                    events.ScheduleEvent(EVENT_QUIVERING_STRIKE, 10000);
                    break;
                case EVENT_IMPENDING_DESPAIR:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    {
                        DoScriptText(SAY_IMPENDING_DESPAIR, me);
                        DoCast(target, SPELL_IMPENDING_DESPAIR);
                    }
                    events.ScheduleEvent(EVENT_IMPENDING_DESPAIR, 13000);
                    break;
                case EVENT_DEFILING_HORROR:
                    DoCast(SPELL_DEFILING_HORROR);
                    events.ScheduleEvent(EVENT_DEFILING_HORROR, urand(25000, 45000)); // TODO adjust timer.
                    break;
            }

            if ((uiHopelessnessCount < 1 && HealthBelowPct(66))
                || (uiHopelessnessCount < 2 && HealthBelowPct(33))
                || (uiHopelessnessCount < 3 && HealthBelowPct(10)))
            {
                uiHopelessnessCount++;
                DoCast(DUNGEON_MODE(SPELL_HOPELESSNESS, H_SPELL_HOPELESSNESS));
            }

            DoMeleeAttackIfReady();
        }
    };

};

void AddSC_boss_falric()
{
    new boss_falric();
}
