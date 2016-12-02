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

#ifndef _VMAPFACTORY_H
#define _VMAPFACTORY_H

#include "IVMapManager.h"

/**
This is the access point to the VMapManager.
*/

namespace VMAP
{
    //===========================================================

    class VMapFactory
    {
        public:
            static IVMapManager* createOrGetVMapManager();
            static void clear();

            static void preventSpellsFromBeingTestedForLoS(const char* pSpellIdString);
            static bool checkSpellForLoS(unsigned int pSpellId);
    };

}
#endif
