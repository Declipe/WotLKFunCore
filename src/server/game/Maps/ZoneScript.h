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

#ifndef ZONE_SCRIPT_H_
#define ZONE_SCRIPT_H_

#include "Common.h"
#include "Creature.h"

class GameObject;

class ZoneScript
{
    public:
        ZoneScript() {}
        virtual ~ZoneScript() {}

        virtual uint32 GetCreatureEntry(uint32 /*guidlow*/, CreatureData const* data) { return data->id; }
        virtual uint32 GetGameObjectEntry(uint32 /*guidlow*/, uint32 entry) { return entry; }

        virtual void OnCreatureCreate(Creature* /*creature*/) {}
        virtual void OnCreatureRemove(Creature* /*creature*/) {}
        virtual void OnGameObjectCreate(GameObject* /*go*/) {}
        virtual void OnGameObjectRemove(GameObject* /*go*/) {}

        virtual void OnUnitDeath(Unit* /*unit*/) {}

        //All-purpose data storage 64 bit
        virtual uint64 GetData64(uint32 /*DataId*/) { return 0; }
        virtual void SetData64(uint32 /*DataId*/, uint64 /*Value*/) {}

        //All-purpose data storage 32 bit
        virtual uint32 GetData(uint32 /*DataId*/) { return 0; }
        virtual void SetData(uint32 /*DataId*/, uint32 /*Value*/) {}

        virtual void ProcessEvent(WorldObject* /*obj*/, uint32 /*eventId*/) {}
};

#endif
