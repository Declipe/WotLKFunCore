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

#include "Player.h"
#include "Battleground.h"
#include "BattlegroundRB.h"
#include "Language.h"

BattlegroundRB::BattlegroundRB()
{
    //TODO FIX ME!
    StartMessageIds[BG_STARTING_EVENT_FIRST]  = 0;
    StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_BG_WS_START_ONE_MINUTE;
    StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_BG_WS_START_HALF_MINUTE;
    StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_BG_WS_HAS_BEGUN;
}

BattlegroundRB::~BattlegroundRB()
{

}

void BattlegroundRB::StartingEventCloseDoors()
{
}

void BattlegroundRB::StartingEventOpenDoors()
{
}

void BattlegroundRB::AddPlayer(Player* player)
{
    Battleground::AddPlayer(player);
    //create score and add it to map, default values are set in constructor
    BattlegroundRBScore* sc = new BattlegroundRBScore;

    PlayerScores[player->GetGUID()] = sc;
}

void BattlegroundRB::RemovePlayer(Player* /*player*/, uint64 /*guid*/, uint32 /*team*/)
{
}

void BattlegroundRB::HandleAreaTrigger(Player* /*Source*/, uint32 /*Trigger*/)
{
    // this is wrong way to implement these things. On official it done by gameobject spell cast.
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;
}

void BattlegroundRB::UpdatePlayerScore(Player* Source, uint32 type, uint32 value, bool doAddHonor)
{
    std::map<uint64, BattlegroundScore*>::iterator itr = PlayerScores.find(Source->GetGUID());

    if (itr == PlayerScores.end())                         // player not found...
        return;

    Battleground::UpdatePlayerScore(Source, type, value, doAddHonor);
}
