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

#include "PacketLog.h"
#include "Config.h"
#include "ByteBuffer.h"
#include "WorldPacket.h"

PacketLog::PacketLog() : _file(NULL)
{
    Initialize();
}

PacketLog::~PacketLog()
{
    if (_file)
        fclose(_file);

    _file = NULL;
}

void PacketLog::Initialize()
{
    std::string logsDir = ConfigMgr::GetStringDefault("LogsDir", "");

    if (!logsDir.empty())
        if ((logsDir.at(logsDir.length()-1) != '/') && (logsDir.at(logsDir.length()-1) != '\\'))
            logsDir.push_back('/');

    std::string logname = ConfigMgr::GetStringDefault("PacketLogFile", "");
    if (!logname.empty())
        _file = fopen((logsDir + logname).c_str(), "wb");
}

void PacketLog::LogPacket(WorldPacket const& packet, Direction direction)
{
    ByteBuffer data(4+4+4+1+packet.size());
    data << int32(packet.GetOpcode());
    data << int32(packet.size());
    data << uint32(time(NULL));
    data << uint8(direction);

    for (uint32 i = 0; i < packet.size(); i++)
        data << const_cast<WorldPacket&>(packet)[i];

    fwrite(data.contents(), 1, data.size(), _file);
    fflush(_file);
}
