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

#ifndef TRANSPORTS_H
#define TRANSPORTS_H

#include "GameObject.h"

#include <map>
#include <set>
#include <string>

class Transport : public GameObject
{
    public:
        Transport(uint32 period, uint32 script);
        ~Transport();

        bool Create(uint32 guidlow, uint32 entry, uint32 mapid, float x, float y, float z, float ang, uint32 animprogress, uint32 dynflags);
        bool GenerateWaypoints(uint32 pathid, std::set<uint32> &mapids);
        void Update(uint32 p_time);
        bool AddPassenger(Player* passenger);
        bool RemovePassenger(Player* passenger);

        void RemovePassenger(Creature* passenger) { m_NPCPassengerSet.erase(passenger); }

        typedef std::set<Player*> PlayerSet;
        PlayerSet const& GetPassengers() const { return m_passengers; }

        typedef std::set<Creature*> CreatureSet;
        CreatureSet m_NPCPassengerSet;
        uint32 AddNPCPassenger(uint32 tguid, uint32 entry, float x, float y, float z, float o, uint32 anim=0);
        void UpdatePosition(MovementInfo* mi);
        void UpdateNPCPositions();
        void BuildStartMovePacket(Map const* targetMap);
        void BuildStopMovePacket(Map const* targetMap);
        uint32 GetScriptId() const { return ScriptId; }
    private:
        struct WayPoint
        {
            WayPoint() : mapid(0), x(0), y(0), z(0), teleport(false), id(0) {}
            WayPoint(uint32 _mapid, float _x, float _y, float _z, bool _teleport, uint32 _id = 0,
                uint32 _arrivalEventID = 0, uint32 _departureEventID = 0)
                : mapid(_mapid), x(_x), y(_y), z(_z), teleport(_teleport), id(_id),
                arrivalEventID(_arrivalEventID), departureEventID(_departureEventID)
            {
            }
            uint32 mapid;
            float x;
            float y;
            float z;
            bool teleport;
            uint32 id;
            uint32 arrivalEventID;
            uint32 departureEventID;
        };

        typedef std::map<uint32, WayPoint> WayPointMap;

        WayPointMap::const_iterator m_curr;
        WayPointMap::const_iterator m_next;
        uint32 m_pathTime;
        uint32 m_timer;

        PlayerSet m_passengers;

        uint32 currenttguid;
        uint32 m_period;
        uint32 ScriptId;
    public:
        WayPointMap m_WayPoints;
        uint32 m_nextNodeTime;

    private:
        void TeleportTransport(uint32 newMapid, float x, float y, float z);
        void UpdateForMap(Map const* map);
        void DoEventIfAny(WayPointMap::value_type const& node, bool departure);
        WayPointMap::const_iterator GetNextWayPoint();
};
#endif
