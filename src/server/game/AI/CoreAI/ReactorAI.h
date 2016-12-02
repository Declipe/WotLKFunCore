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

#ifndef TRINITY_REACTORAI_H
#define TRINITY_REACTORAI_H

#include "CreatureAI.h"

class Unit;

class ReactorAI : public CreatureAI
{
    public:

        explicit ReactorAI(Creature* c) : CreatureAI(c) {}

        void MoveInLineOfSight(Unit*);

        void UpdateAI(const uint32);
        static int Permissible(const Creature*);
};
#endif

