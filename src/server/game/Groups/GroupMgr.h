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

#ifndef _GROUPMGR_H
#define _GROUPMGR_H

#include "Group.h"

class GroupMgr
{
    friend class ACE_Singleton<GroupMgr, ACE_Null_Mutex>;
private:
    GroupMgr();
    ~GroupMgr();

public:
    typedef std::map<uint32, Group*> GroupContainer;
    typedef std::vector<Group*>      GroupDbContainer;

    Group* GetGroupByGUID(uint32 guid) const;

    uint32 GenerateNewGroupDbStoreId();
    void   RegisterGroupDbStoreId(uint32 storageId, Group* group);
    void   FreeGroupDbStoreId(Group* group);
    void   SetNextGroupDbStoreId(uint32 storageId) { NextGroupDbStoreId = storageId; };
    Group* GetGroupByDbStoreId(uint32 storageId) const;
    void   SetGroupDbStoreSize(uint32 newSize) { GroupDbStore.resize(newSize); }

    void   LoadGroups();
    uint32 GenerateGroupId();
    void   AddGroup(Group* group);
    void   RemoveGroup(Group* group);


protected:
    uint32           NextGroupId;
    uint32           NextGroupDbStoreId;
    GroupContainer   GroupStore;
    GroupDbContainer GroupDbStore;
};

#define sGroupMgr ACE_Singleton<GroupMgr, ACE_Null_Mutex>::instance()

#endif
