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

#ifndef TRINITY_COMBATAI_H
#define TRINITY_COMBATAI_H

#include "CreatureAI.h"
#include "CreatureAIImpl.h"
#include "ConditionMgr.h"

class Creature;

class AggressorAI : public CreatureAI
{
    public:
        explicit AggressorAI(Creature* c) : CreatureAI(c) {}

        void UpdateAI(const uint32);
        static int Permissible(const Creature*);
};

typedef std::vector<uint32> SpellVct;

class CombatAI : public CreatureAI
{
    public:
        explicit CombatAI(Creature* c) : CreatureAI(c) {}

        void InitializeAI();
        void Reset();
        void EnterCombat(Unit* who);
        void JustDied(Unit* killer);
        void UpdateAI(const uint32 diff);
        void SpellInterrupted(uint32 spellId, uint32 unTimeMs);
        static int Permissible(const Creature*);
    protected:
        EventMap events;
        SpellVct spells;
};

class CasterAI : public CombatAI
{
    public:
        explicit CasterAI(Creature* c) : CombatAI(c) { m_attackDist = MELEE_RANGE; }
        void InitializeAI();
        void AttackStart(Unit* victim) { AttackStartCaster(victim, m_attackDist); }
        void UpdateAI(const uint32 diff);
        void EnterCombat(Unit* /*who*/);
    private:
        float m_attackDist;
};

struct ArcherAI : public CreatureAI
{
    public:
        explicit ArcherAI(Creature* c);
        void AttackStart(Unit* who);
        void UpdateAI(const uint32 diff);

        static int Permissible(const Creature*);
    protected:
        float m_minRange;
};

struct TurretAI : public CreatureAI
{
    public:
        explicit TurretAI(Creature* c);
        bool CanAIAttack(const Unit* who) const;
        void AttackStart(Unit* who);
        void UpdateAI(const uint32 diff);

        static int Permissible(const Creature*);
    protected:
        float m_minRange;
};

#define VEHICLE_CONDITION_CHECK_TIME 1000
#define VEHICLE_DISMISS_TIME 5000
struct VehicleAI : public CreatureAI
{
    public:
        explicit VehicleAI(Creature* c);

        void UpdateAI(const uint32 diff);
        static int Permissible(const Creature*);
        void Reset();
        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit*) {}
        void OnCharmed(bool apply);

    private:
        Vehicle* m_vehicle;
        bool m_IsVehicleInUse;
        void LoadConditions();
        void CheckConditions(const uint32 diff);
        ConditionList conditions;
        uint32 m_ConditionsTimer;
        bool m_DoDismiss;
        uint32 m_DismissTimer;
};

#endif
