/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2006-2016 MaNGOS.
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

#include "SHA1.h"

#ifndef _WARDEN_KEY_GENERATION_H
#define _WARDEN_KEY_GENERATION_H

class SHA1Randx {
public:
    SHA1Randx(uint8 *buff, uint32 size) {
        uint32 taken = size/2;

        sh.Initialize();
        sh.UpdateData(buff,taken);
        sh.Finalize();

        memcpy(o1,sh.GetDigest(),20);

        sh.Initialize();
        sh.UpdateData(buff+taken,size-taken);
        sh.Finalize();

        memcpy(o2,sh.GetDigest(),20);

        memset(o0,0x00,20);

        fillUp();
    }

    void generate(uint8 *buf, uint32 sz) {
        for(uint32 i=0;i<sz;i++) {
            if(taken == 20) {
                fillUp();
            }

            buf[i] = o0[taken];
            taken++;
        }
    }
private:
    void fillUp() {
        sh.Initialize();
        sh.UpdateData(o1,20);
        sh.UpdateData(o0,20);
        sh.UpdateData(o2,20);
        sh.Finalize();

        memcpy(o0,sh.GetDigest(),20);

        taken = 0;
    }
    SHA1Hash sh;
    uint32 taken;
    uint8 o0[20],o1[20],o2[20];
};

#endif
