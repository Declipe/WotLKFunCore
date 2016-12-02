/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2006-2016 ScriptDev2.
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

/* ScriptData
SDName: Deadmines
SD%Complete: 0
SDComment: Placeholder
SDCategory: Deadmines
EndScriptData */

#include "ScriptPCH.h"
#include "deadmines.h"
#include "Spell.h"

/*#####
# item_Defias_Gunpowder
#####*/

class item_defias_gunpowder : public ItemScript
{
public:
    item_defias_gunpowder() : ItemScript("item_defias_gunpowder") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        InstanceScript* instance = player->GetInstanceScript();

        if (!instance)
        {
            player->GetSession()->SendNotification("Instance script not initialized");
            return true;
        }

        if (instance->GetData(EVENT_STATE) != CANNON_NOT_USED)
            return false;

        if (targets.GetGOTarget() && targets.GetGOTarget()->GetEntry() == GO_DEFIAS_CANNON)
            instance->SetData(EVENT_STATE, CANNON_GUNPOWDER_USED);

        player->DestroyItemCount(item->GetEntry(), 1, true);
        return true;
    }
};

void AddSC_deadmines()
{
    new item_defias_gunpowder();
}
