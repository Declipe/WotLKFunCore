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

#ifndef __TRINITY_CHANNELMGR_H
#define __TRINITY_CHANNELMGR_H

#include "Common.h"
#include "Channel.h"
#include <ace/Singleton.h>

#include <map>
#include <string>

#include "World.h"

class ChannelMgr
{
    public:
        uint32 team;
        typedef std::map<std::wstring, Channel*> ChannelMap;
        ChannelMgr() {team = 0;}
        ~ChannelMgr();

        Channel* GetJoinChannel(std::string name, uint32 channel_id);
        Channel* GetChannel(std::string name, Player* p, bool pkt = true);
        void LeftChannel(std::string name);
    private:
        ChannelMap channels;
        void MakeNotOnPacket(WorldPacket* data, std::string name);
};

class AllianceChannelMgr : public ChannelMgr {};
class HordeChannelMgr    : public ChannelMgr {};

ChannelMgr* channelMgr(uint32 team);

#endif

