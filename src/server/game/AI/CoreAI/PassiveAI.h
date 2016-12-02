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

#ifndef TRINITY_PASSIVEAI_H
#define TRINITY_PASSIVEAI_H

#include "CreatureAI.h"
//#include "CreatureAIImpl.h"

class PassiveAI : public CreatureAI
{
    public:
        explicit PassiveAI(Creature* c);

        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit*) {}
        void UpdateAI(const uint32);

        static int Permissible(const Creature*) { return PERMIT_BASE_IDLE;  }
};

class PossessedAI : public CreatureAI
{
    public:
        explicit PossessedAI(Creature* c);

        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit* target);
        void UpdateAI(const uint32);
        void EnterEvadeMode() {}

        void JustDied(Unit*);
        void KilledUnit(Unit* victim);

        static int Permissible(const Creature*) { return PERMIT_BASE_IDLE;  }
};

class NullCreatureAI : public CreatureAI
{
    public:
        explicit NullCreatureAI(Creature* c);

        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit*) {}
        void UpdateAI(const uint32) {}
        void EnterEvadeMode() {}
        void OnCharmed(bool /*apply*/) {}

        static int Permissible(const Creature*) { return PERMIT_BASE_IDLE;  }
};

class CritterAI : public PassiveAI
{
    public:
        explicit CritterAI(Creature* c) : PassiveAI(c) {}

        void DamageTaken(Unit* done_by, uint32& /*damage*/);
        void EnterEvadeMode();
};

class TriggerAI : public NullCreatureAI
{
    public:
        explicit TriggerAI(Creature* c) : NullCreatureAI(c) {}
        void IsSummonedBy(Unit* summoner);
};

#endif

