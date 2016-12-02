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

#ifndef _LFGGROUPDATA_H
#define _LFGGROUPDATA_H

#include "LFG.h"

enum LfgGroupEnum
{
    LFG_GROUP_MAX_KICKS                           = 3,
    LFG_GROUP_KICK_VOTES_NEEDED                   = 3
};

/**
    Stores all lfg data needed about a group.
*/
class LfgGroupData
{
    public:
        LfgGroupData();
        ~LfgGroupData();

        // General
        void SetState(LfgState state);
        void RestoreState();
        // Dungeon
        void SetDungeon(uint32 dungeon);
        // VoteKick
        void SetVotesNeeded(uint8 votes);
        void DecreaseKicksLeft();

        // General
        LfgState GetState() const;
        // Dungeon
        uint32 GetDungeon(bool asId = true) const;
        // VoteKick
        uint8 GetVotesNeeded() const;
        uint8 GetKicksLeft() const;

    private:
        // General
        LfgState m_State;                                  ///< State if group in LFG
        LfgState m_OldState;                               ///< Old State
        // Dungeon
        uint32 m_Dungeon;                                  ///< Dungeon entry
        // Vote Kick
        uint8 m_VotesNeeded;                               ///< Votes need to kick success
        uint8 m_KicksLeft;                                 ///< Number of kicks left
};

#endif
