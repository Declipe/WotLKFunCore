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

#ifndef TRINITY_GUARDAI_H
#define TRINITY_GUARDAI_H

#include "ScriptedCreature.h"
#include "Timer.h"

class Creature;

class GuardAI : public ScriptedAI
{
    enum GuardState
    {
        STATE_NORMAL = 1,
        STATE_LOOK_AT_VICTIM = 2
    };

    public:

        explicit GuardAI(Creature* c);

        void MoveInLineOfSight(Unit*);
        void EnterEvadeMode();
        void JustDied(Unit*);
        bool CanSeeAlways(WorldObject const* obj);

        void UpdateAI(const uint32);
        static int Permissible(const Creature*);

    private:
        uint64 i_victimGuid;
        GuardState i_state;
        TimeTracker i_tracker;
};
#endif

