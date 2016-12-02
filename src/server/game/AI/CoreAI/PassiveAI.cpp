/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2005-2016 MaNGOS.
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

#include "PassiveAI.h"
#include "Creature.h"
#include "TemporarySummon.h"

PassiveAI::PassiveAI(Creature* c) : CreatureAI(c) { me->SetReactState(REACT_PASSIVE); }
PossessedAI::PossessedAI(Creature* c) : CreatureAI(c) { me->SetReactState(REACT_PASSIVE); }
NullCreatureAI::NullCreatureAI(Creature* c) : CreatureAI(c) { me->SetReactState(REACT_PASSIVE); }

void PassiveAI::UpdateAI(const uint32)
{
    if (me->isInCombat() && me->getAttackers().empty())
        EnterEvadeMode();
}

void PossessedAI::AttackStart(Unit* target)
{
    me->Attack(target, true);
}

void PossessedAI::UpdateAI(const uint32 /*diff*/)
{
    if (me->getVictim())
    {
        if (!me->IsValidAttackTarget(me->getVictim()))
            me->AttackStop();
        else
            DoMeleeAttackIfReady();
    }
}

void PossessedAI::JustDied(Unit* /*u*/)
{
    // We died while possessed, disable our loot
    me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
}

void PossessedAI::KilledUnit(Unit* victim)
{
    // We killed a creature, disable victim's loot
    if (victim->GetTypeId() == TYPEID_UNIT)
        victim->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
}

void CritterAI::DamageTaken(Unit* /*done_by*/, uint32&)
{
    if (!me->HasUnitState(UNIT_STATE_FLEEING))
        me->SetControlled(true, UNIT_STATE_FLEEING);
}

void CritterAI::EnterEvadeMode()
{
    if (me->HasUnitState(UNIT_STATE_FLEEING))
        me->SetControlled(false, UNIT_STATE_FLEEING);
    CreatureAI::EnterEvadeMode();
}

void TriggerAI::IsSummonedBy(Unit* summoner)
{
    if (me->m_spells[0])
        me->CastSpell(me, me->m_spells[0], false, 0, 0, summoner->GetGUID());
}
