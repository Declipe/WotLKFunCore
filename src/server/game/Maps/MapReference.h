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

#ifndef _MAPREFERENCE_H
#define _MAPREFERENCE_H

#include "Reference.h"
#include "Map.h"

class MapReference : public Reference<Map, Player>
{
    protected:
        void targetObjectBuildLink()
        {
            // called from link()
            getTarget()->m_mapRefManager.insertFirst(this);
            getTarget()->m_mapRefManager.incSize();
        }
        void targetObjectDestroyLink()
        {
            // called from unlink()
            if (isValid()) getTarget()->m_mapRefManager.decSize();
        }
        void sourceObjectDestroyLink()
        {
            // called from invalidate()
            getTarget()->m_mapRefManager.decSize();
        }
    public:
        MapReference() : Reference<Map, Player>() {}
        ~MapReference() { unlink(); }
        MapReference* next() { return (MapReference*)Reference<Map, Player>::next(); }
        MapReference const* next() const { return (MapReference const*)Reference<Map, Player>::next(); }
        MapReference* nockeck_prev() { return (MapReference*)Reference<Map, Player>::nocheck_prev(); }
        MapReference const* nocheck_prev() const { return (MapReference const*)Reference<Map, Player>::nocheck_prev(); }
};
#endif

