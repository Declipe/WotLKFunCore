# WotLKFunCore is a custom fun server built for
# World of Warcarft game build 3.3.5b. (12345)
#
# Copyright (C) 2008-2016 JustACore.
# Copyright (C) 2008-2016 TrinityCore.
#
# ==== Start of GNU GPL ====
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# ==== End of GNU GPL ====
#

file(GLOB sources src/*.c)

set(jemalloc_STAT_SRC
  ${sources}
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_definitions(-D_GNU_SOURCE -D_REENTRANT)

add_library(jemalloc STATIC ${sources})
