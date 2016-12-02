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

#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Log.h"

void WorldSession::HandleVoiceSessionEnableOpcode(WorldPacket& recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_VOICE_SESSION_ENABLE");
    // uint8 isVoiceEnabled, uint8 isMicrophoneEnabled
    recv_data.read_skip<uint8>();
    recv_data.read_skip<uint8>();
}

void WorldSession::HandleChannelVoiceOnOpcode(WorldPacket& /*recv_data*/)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CHANNEL_VOICE_ON");
    // Enable Voice button in channel context menu
}

void WorldSession::HandleSetActiveVoiceChannel(WorldPacket& recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_SET_ACTIVE_VOICE_CHANNEL");
    recv_data.read_skip<uint32>();
    recv_data.read_skip<char*>();
}

