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

#ifndef TRINITY_UNORDERED_MAP_H
#define TRINITY_UNORDERED_MAP_H

#include "CompilerDefs.h"
#include "Define.h"

#if COMPILER == COMPILER_INTEL
#include <ext/hash_map>
#elif COMPILER == COMPILER_GNU && (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 3)
#include <tr1/unordered_map>
#elif COMPILER == COMPILER_GNU && __GNUC__ >= 3
#include <ext/hash_map>
#elif COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1500 && _HAS_TR1    // VC9.0 and later
#include <unordered_map>
#else
#include <hash_map>
#endif

#ifdef _STLPORT_VERSION
#define UNORDERED_MAP std::hash_map
using std::hash_map;
#elif COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1500 && _HAS_TR1
#define UNORDERED_MAP std::tr1::unordered_map
#elif COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1300
#define UNORDERED_MAP stdext::hash_map
using stdext::hash_map;
#elif COMPILER == COMPILER_GNU && (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 3)
#define UNORDERED_MAP std::tr1::unordered_map
#elif (COMPILER == COMPILER_GNU && __GNUC__ >= 3) || COMPILER == COMPILER_INTEL
#define UNORDERED_MAP __gnu_cxx::hash_map

namespace __gnu_cxx
{
    template<> struct hash<unsigned long long>
    {
        size_t operator()(const unsigned long long &__x) const { return (size_t)__x; }
    };
    template<typename T> struct hash<T *>
    {
        size_t operator()(T * const &__x) const { return (size_t)__x; }
    };
    template<> struct hash<std::string>
    {
        size_t operator()(const std::string &__x) const
        {
            return hash<const char *>()(__x.c_str());
        }
    };
};

#else
#define UNORDERED_MAP std::hash_map
using std::hash_map;
#endif
#endif
