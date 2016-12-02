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

#ifndef _REALMLIST_H
#define _REALMLIST_H

#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>
#include "Common.h"

enum RealmFlags
{
    REALM_FLAG_NONE                              = 0x00,
    REALM_FLAG_INVALID                           = 0x01,
    REALM_FLAG_OFFLINE                           = 0x02,
    REALM_FLAG_SPECIFYBUILD                      = 0x04,
    REALM_FLAG_UNK1                              = 0x08,
    REALM_FLAG_UNK2                              = 0x10,
    REALM_FLAG_RECOMMENDED                       = 0x20,
    REALM_FLAG_NEW                               = 0x40,
    REALM_FLAG_FULL                              = 0x80
};

// Storage object for a realm
struct Realm
{
    std::string address;
    std::string name;
    uint8 icon;
    RealmFlags flag;
    uint8 timezone;
    uint32 m_ID;
    AccountTypes allowedSecurityLevel;
    float populationLevel;
    uint32 gamebuild;
};

/// Storage object for the list of realms on the server
class RealmList
{
public:
    typedef std::map<std::string, Realm> RealmMap;

    RealmList();
    ~RealmList() {}

    void Initialize(uint32 updateInterval);

    void UpdateIfNeed();

    void AddRealm(Realm NewRealm) {m_realms[NewRealm.name] = NewRealm;}

    RealmMap::const_iterator begin() const { return m_realms.begin(); }
    RealmMap::const_iterator end() const { return m_realms.end(); }
    uint32 size() const { return m_realms.size(); }

private:
    void UpdateRealms(bool init=false);
    void UpdateRealm(uint32 ID, const std::string& name, const std::string& address, uint16 port, uint8 icon, RealmFlags flag, uint8 timezone, AccountTypes allowedSecurityLevel, float popu, uint32 build);

    RealmMap m_realms;
    uint32   m_UpdateInterval;
    time_t   m_NextUpdateTime;
};

#define sRealmList ACE_Singleton<RealmList, ACE_Null_Mutex>::instance()
#endif
