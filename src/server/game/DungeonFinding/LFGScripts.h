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

/*
 * Interaction between core and LFGScripts
 */

#include "Common.h"
#include "SharedDefines.h"
#include "ScriptPCH.h"

class Player;
class Group;

class LFGPlayerScript : public PlayerScript
{
    public:
        LFGPlayerScript();

        // Player Hooks
        void OnLevelChanged(Player* player, uint8 oldLevel);
        void OnLogout(Player* player);
        void OnLogin(Player* player);
        void OnBindToInstance(Player* player, Difficulty difficulty, uint32 mapId, bool permanent);
};

class LFGGroupScript : public GroupScript
{
    public:
        LFGGroupScript();

        // Group Hooks
        void OnAddMember(Group* group, uint64 guid);
        void OnRemoveMember(Group* group, uint64 guid, RemoveMethod method, uint64 kicker, char const* reason);
        void OnDisband(Group* group);
        void OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid);
        void OnInviteMember(Group* group, uint64 guid);
};
