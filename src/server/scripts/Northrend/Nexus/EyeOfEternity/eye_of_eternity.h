/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
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

#ifndef DEF_EYE_OF_ETERNITY_H
#define DEF_EYE_OF_ETERNITY_H

enum InstanceData
{
    DATA_MALYGOS_EVENT,
    MAX_ENCOUNTER,

    DATA_VORTEX_HANDLING,
    DATA_POWER_SPARKS_HANDLING
};

enum InstanceData64
{
    DATA_TRIGGER,
    DATA_MALYGOS,
    DATA_PLATFORM
};

enum InstanceNpcs
{
    NPC_MALYGOS             = 28859,
    NPC_VORTEX_TRIGGER      = 30090,
    NPC_PORTAL_TRIGGER      = 30118,
    NPC_POWER_SPARK         = 30084,
    NPC_HOVER_DISK_MELEE    = 30234,
    NPC_HOVER_DISK_CASTER   = 30248,
    NPC_ARCANE_OVERLOAD     = 30282,
    NPC_WYRMREST_SKYTALON   = 30161,
    NPC_ALEXSTRASZA         = 32295
};

enum InstanceGameObjects
{
    GO_NEXUS_RAID_PLATFORM      = 193070,
    GO_EXIT_PORTAL              = 193908,
    GO_FOCUSING_IRIS            = 193958,
    GO_ALEXSTRASZA_S_GIFT       = 193905,
    GO_ALEXSTRASZA_S_GIFT_2     = 193967
};

enum InstanceEvents
{
    EVENT_FOCUSING_IRIS = 20711
};

enum InstanceSpells
{
    SPELL_VORTEX_4          = 55853, // damage | used to enter to the vehicle
    SPELL_VORTEX_5          = 56263, // damage | used to enter to the vehicle
    SPELL_PORTAL_OPENED     = 61236,
    SPELL_RIDE_RED_DRAGON   = 56071,
};

#endif
