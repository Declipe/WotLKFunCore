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

#ifndef _FORMATIONS_H
#define _FORMATIONS_H

#include "Define.h"
#include "UnorderedMap.h"
#include <map>

class Creature;
class CreatureGroup;

struct FormationInfo
{
    uint32 leaderGUID;
    float follow_dist;
    float follow_angle;
    uint8 groupAI;
};

typedef UNORDERED_MAP<uint32/*memberDBGUID*/, FormationInfo*>   CreatureGroupInfoType;

class FormationMgr
{
    friend class ACE_Singleton<FormationMgr, ACE_Null_Mutex>;
    public:
        FormationMgr() { }
        ~FormationMgr();
        void AddCreatureToGroup(uint32 group_id, Creature* creature);
        void RemoveCreatureFromGroup(CreatureGroup* group, Creature* creature);
        void LoadCreatureFormations();
        CreatureGroupInfoType CreatureGroupMap;
};

class CreatureGroup
{
    private:
        Creature* m_leader; //Important do not forget sometimes to work with pointers instead synonims :D:D
        typedef std::map<Creature*, FormationInfo*>  CreatureGroupMemberType;
        CreatureGroupMemberType m_members;

        uint32 m_groupID;
        bool m_Formed;

    public:
        //Group cannot be created empty
        explicit CreatureGroup(uint32 id) : m_leader(NULL), m_groupID(id), m_Formed(false) {}
        ~CreatureGroup() {}

        Creature* getLeader() const { return m_leader; }
        uint32 GetId() const { return m_groupID; }
        bool isEmpty() const { return m_members.empty(); }
        bool isFormed() const { return m_Formed; }

        void AddMember(Creature* member);
        void RemoveMember(Creature* member);
        void FormationReset(bool dismiss);

        void LeaderMoveTo(float x, float y, float z);
        void MemberAttackStart(Creature* member, Unit* target);
};

#define sFormationMgr ACE_Singleton<FormationMgr, ACE_Null_Mutex>::instance()

#endif
