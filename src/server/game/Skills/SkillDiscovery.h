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

#ifndef TRINITY_SKILLDISCOVERY_H
#define TRINITY_SKILLDISCOVERY_H

#include "Common.h"

class Player;

void LoadSkillDiscoveryTable();
uint32 GetSkillDiscoverySpell(uint32 skillId, uint32 spellId, Player* player);
bool HasDiscoveredAllSpells(uint32 spellId, Player* player);
uint32 GetExplicitDiscoverySpell(uint32 spellId, Player* player);
#endif
