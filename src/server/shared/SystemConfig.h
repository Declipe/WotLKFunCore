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

// THIS FILE IS DEPRECATED

#ifndef TRINITY_SYSTEMCONFIG_H
#define TRINITY_SYSTEMCONFIG_H

#include "Define.h"
#include "revision.h"

#define _PACKAGENAME "WotLKFunCore"

#if TRINITY_ENDIAN == TRINITY_BIGENDIAN
# define _ENDIAN_STRING "big-endian"
#else
# define _ENDIAN_STRING "little-endian"
#endif

#if PLATFORM == PLATFORM_WINDOWS
# ifdef _WIN64
#  define _FULLVERSION _PACKAGENAME " : " VER_PRODUCTVERSION_STR " (Win64, "_BUILD_DIRECTIVE ")"
# else
#  define _FULLVERSION _PACKAGENAME " : " VER_PRODUCTVERSION_STR " (Win32, " _BUILD_DIRECTIVE ")"
# endif
#else
#  define _FULLVERSION _PACKAGENAME " : " VER_PRODUCTVERSION_STR " (Unix, " _BUILD_DIRECTIVE ")"
#endif
#endif
