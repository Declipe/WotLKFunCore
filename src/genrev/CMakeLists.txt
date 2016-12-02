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

# Need to pass old ${CMAKE_BINARY_DIR} as param because its different at build stage
add_custom_target(revision.h ALL
  COMMAND ${CMAKE_COMMAND} -DBUILDDIR=${CMAKE_BINARY_DIR} -P ${CMAKE_SOURCE_DIR}/cmake/genrev.cmake
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
