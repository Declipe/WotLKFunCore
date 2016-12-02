/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
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

#ifndef TRINITYSERVER_PACKET_BUILDER_H
#define TRINITYSERVER_PACKET_BUILDER_H

class ByteBuffer;
class WorldPacket;

namespace Movement
{
    class MoveSpline;
    class PacketBuilder
    {
        static void WriteCommonMonsterMovePart(const MoveSpline& mov, WorldPacket& data);
    public:

        static void WriteMonsterMove(const MoveSpline& mov, WorldPacket& data);
        static void WriteCreate(const MoveSpline& mov, ByteBuffer& data);
    };
}
#endif // TRINITYSERVER_PACKET_BUILDER_H
