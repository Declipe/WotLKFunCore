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

#include "AuthCrypt.h"
#include "Cryptography/HMACSHA1.h"
#include "Cryptography/BigNumber.h"

AuthCrypt::AuthCrypt() : _clientDecrypt(SHA_DIGEST_LENGTH), _serverEncrypt(SHA_DIGEST_LENGTH)
    , _initialized(false)
{
}

AuthCrypt::~AuthCrypt()
{

}

void AuthCrypt::Init(BigNumber* K)
{
    uint8 ServerEncryptionKey[SEED_KEY_SIZE] = { 0xCC, 0x98, 0xAE, 0x04, 0xE8, 0x97, 0xEA, 0xCA, 0x12, 0xDD, 0xC0, 0x93, 0x42, 0x91, 0x53, 0x57 };
    HmacHash serverEncryptHmac(SEED_KEY_SIZE, (uint8*)ServerEncryptionKey);
    uint8 *encryptHash = serverEncryptHmac.ComputeHash(K);

    uint8 ServerDecryptionKey[SEED_KEY_SIZE] = { 0xC2, 0xB3, 0x72, 0x3C, 0xC6, 0xAE, 0xD9, 0xB5, 0x34, 0x3C, 0x53, 0xEE, 0x2F, 0x43, 0x67, 0xCE };
    HmacHash clientDecryptHmac(SEED_KEY_SIZE, (uint8*)ServerDecryptionKey);
    uint8 *decryptHash = clientDecryptHmac.ComputeHash(K);

    //ARC4 _serverDecrypt(encryptHash);
    _clientDecrypt.Init(decryptHash);
    _serverEncrypt.Init(encryptHash);
    //ARC4 _clientEncrypt(decryptHash);

    // Drop first 1024 bytes, as WoW uses ARC4-drop1024.
    uint8 syncBuf[1024];
    memset(syncBuf, 0, 1024);

    _serverEncrypt.UpdateData(1024, syncBuf);
    //_clientEncrypt.UpdateData(1024, syncBuf);

    memset(syncBuf, 0, 1024);

    //_serverDecrypt.UpdateData(1024, syncBuf);
    _clientDecrypt.UpdateData(1024, syncBuf);

    _initialized = true;
}

void AuthCrypt::DecryptRecv(uint8 *data, size_t len)
{
    if (!_initialized)
        return;

    _clientDecrypt.UpdateData(len, data);
}

void AuthCrypt::EncryptSend(uint8 *data, size_t len)
{
    if (!_initialized)
        return;

    _serverEncrypt.UpdateData(len, data);
}

