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

#ifndef TRINITY_GRIDSTATES_H
#define TRINITY_GRIDSTATES_H

#include "Map.h"
#include "Object.h"

class GridState
{
    public:
#ifdef TRINITY_DEBUG
#define MAGIC_TESTVAL 0xFBE823BA
        GridState() { i_Magic = MAGIC_TESTVAL; }
        bool checkMagic()
        {
            if (i_Magic != MAGIC_TESTVAL)
            {
                sLog->outError("!!! GridState: Magic value gone !!!");
                return false;
            }
            return true;
        }
        void setMagic() { i_Magic = MAGIC_TESTVAL; }
        unsigned int i_Magic;
#endif
        virtual ~GridState() {};
        virtual void Update(Map &, NGridType&, GridInfo &, const uint32 t_diff) const = 0;
};

class InvalidState : public GridState
{
    public:
        void Update(Map &, NGridType &, GridInfo &, const uint32 t_diff) const;
};

class ActiveState : public GridState
{
    public:
        void Update(Map &, NGridType &, GridInfo &, const uint32 t_diff) const;
};

class IdleState : public GridState
{
    public:
        void Update(Map &, NGridType &, GridInfo &, const uint32 t_diff) const;
};

class RemovalState : public GridState
{
    public:
        void Update(Map &, NGridType &, GridInfo &, const uint32 t_diff) const;
};
#endif

