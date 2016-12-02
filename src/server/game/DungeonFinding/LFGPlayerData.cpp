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

#include "LFGPlayerData.h"

LfgPlayerData::LfgPlayerData():
m_State(LFG_STATE_NONE), m_OldState(LFG_STATE_NONE), m_Roles(0), m_Comment("")
{}

LfgPlayerData::~LfgPlayerData()
{
}

void LfgPlayerData::SetState(LfgState state)
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

void LfgPlayerData::ClearState()
{
    m_SelectedDungeons.clear();
    m_Roles = 0;
    m_State = m_OldState;
}

void LfgPlayerData::SetLockedDungeons(const LfgLockMap& lockStatus)
{
    m_LockedDungeons = lockStatus;
}

void LfgPlayerData::SetRoles(uint8 roles)
{
    m_Roles = roles;
}

void LfgPlayerData::SetComment(const std::string& comment)
{
    m_Comment = comment;
}

void LfgPlayerData::SetSelectedDungeons(const LfgDungeonSet& dungeons)
{
    m_SelectedDungeons = dungeons;
}

void LfgPlayerData::ClearSelectedDungeons()
{
    m_SelectedDungeons.clear();
}

LfgState LfgPlayerData::GetState() const
{
    return m_State;
}

const LfgLockMap & LfgPlayerData::GetLockedDungeons() const
{
    return m_LockedDungeons;
}

uint8 LfgPlayerData::GetRoles() const
{
    return m_Roles;
}

const std::string& LfgPlayerData::GetComment() const
{
    return m_Comment;
}

const LfgDungeonSet& LfgPlayerData::GetSelectedDungeons() const
{
    return m_SelectedDungeons;
}
