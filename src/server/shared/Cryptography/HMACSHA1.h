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

#ifndef _AUTH_HMAC_H
#define _AUTH_HMAC_H

#include "Define.h"
#include <string>
#include <openssl/hmac.h>
#include <openssl/sha.h>

class BigNumber;

#define SEED_KEY_SIZE 16

class HmacHash
{
    public:
        HmacHash(uint32 len, uint8 *seed);
        ~HmacHash();
        void UpdateData(const std::string &str);
        void Finalize();
        uint8 *ComputeHash(BigNumber* bn);
        uint8 *GetDigest() { return (uint8*)m_digest; }
        int GetLength() const { return SHA_DIGEST_LENGTH; }
    private:
        HMAC_CTX m_ctx;
        uint8 m_digest[SHA_DIGEST_LENGTH];
};
#endif

