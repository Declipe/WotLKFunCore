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

#ifndef TRINITY_PETAI_H
#define TRINITY_PETAI_H

#include "CreatureAI.h"
#include "Timer.h"

class Creature;
class Spell;

class PetAI : public CreatureAI
{
    public:

        explicit PetAI(Creature* c);

        void EnterEvadeMode();
        void JustDied(Unit* /*who*/) { _stopAttack(); }

        void UpdateAI(const uint32);
        static int Permissible(const Creature*);

        void KilledUnit(Unit* /*victim*/);
        void AttackStart(Unit* target);
        void MovementInform(uint32 moveType, uint32 data);
        void OwnerDamagedBy(Unit* attacker);
        void OwnerAttacked(Unit* target);

    private:
        bool _isVisible(Unit*) const;
        bool _needToStop(void);
        void _stopAttack(void);

        void UpdateAllies();

        TimeTracker i_tracker;
        bool inCombat;
        std::set<uint64> m_AllySet;
        uint32 m_updateAlliesTimer;

        Unit* SelectNextTarget();
        void HandleReturnMovement();
        void DoAttack(Unit* target, bool chase);
        bool CanAttack(Unit* target);
};
#endif

