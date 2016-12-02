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

#include "LFG.h"
#include "LFGGroupData.h"

LfgGroupData::LfgGroupData():
m_State(LFG_STATE_NONE), m_OldState(LFG_STATE_NONE), m_Dungeon(0),
m_VotesNeeded(LFG_GROUP_KICK_VOTES_NEEDED), m_KicksLeft(LFG_GROUP_MAX_KICKS)
{
}

LfgGroupData::~LfgGroupData()
{
}

void LfgGroupData::SetState(LfgState state)
{
    switch (state)
    {
        case LFG_STATE_NONE:
        case LFG_STATE_DUNGEON:
        case LFG_STATE_FINISHED_DUNGEON:
            m_OldState = state;
                    // No break on purpose
        default:
            m_State = state;
    }
}

void LfgGroupData::RestoreState()
{
    m_State = m_OldState;
}

void LfgGroupData::SetDungeon(uint32 dungeon)
{
    m_Dungeon = dungeon;
}

void LfgGroupData::DecreaseKicksLeft()
{
    if (m_KicksLeft)
      --m_KicksLeft;
}

LfgState LfgGroupData::GetState() const
{
    return m_State;
}

uint32 LfgGroupData::GetDungeon(bool asId /* = true */) const
{
    if (asId)
        return (m_Dungeon & 0x00FFFFFF);
    else
        return m_Dungeon;
}

uint8 LfgGroupData::GetVotesNeeded() const
{
    return m_VotesNeeded;
}

uint8 LfgGroupData::GetKicksLeft() const
{
    return m_KicksLeft;
}
