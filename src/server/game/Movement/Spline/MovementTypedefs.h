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

#ifndef TRINITYSERVER_TYPEDEFS_H
#define TRINITYSERVER_TYPEDEFS_H

#include "Common.h"

namespace G3D
{
    class Vector2;
    class Vector3;
    class Vector4;
}

namespace Movement
{
    using G3D::Vector2;
    using G3D::Vector3;
    using G3D::Vector4;

    inline uint32 SecToMS(float sec)
    {
        return static_cast<uint32>(sec * 1000.f);
    }

    inline float MSToSec(uint32 ms)
    {
        return ms / 1000.f;
    }

#ifndef static_assert
    #define CONCAT(x, y) CONCAT1 (x, y)
    #define CONCAT1(x, y) x##y
    #define static_assert(expr, msg) typedef char CONCAT(static_assert_failed_at_line_, __LINE__) [(expr) ? 1 : -1]
#endif

    template<class T, T limit>
    class counter
    {
    public:
        counter() { init();}

        void Increase()
        {
            if (m_counter == limit)
                init();
            else
                ++m_counter;
        }

        T NewId() { Increase(); return m_counter;}
        T getCurrent() const { return m_counter;}

    private:
        void init() { m_counter = 0; }
        T m_counter;
    };

    typedef counter<uint32, 0xFFFFFFFF> UInt32Counter;

    extern double gravity;
    extern float computeFallElevation(float t_passed, bool isSafeFall, float start_velocity);
}

#endif // TRINITYSERVER_TYPEDEFS_H
