# WotLKFunCore is a custom server built for
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

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Spells/spell_shaman.cpp
  Spells/spell_hunter.cpp
  Spells/spell_rogue.cpp
  Spells/spell_druid.cpp
  Spells/spell_dk.cpp
  Spells/spell_quest.cpp
  Spells/spell_warrior.cpp
  Spells/spell_generic.cpp
  Spells/spell_warlock.cpp
  Spells/spell_priest.cpp
  Spells/spell_mage.cpp
  Spells/spell_paladin.cpp
  Spells/spell_item.cpp
  Spells/spell_holiday.cpp
)

message("  -> Prepared: Spells")
