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
SDName: Example_Misc
SD%Complete: 100
SDComment: Item, Areatrigger and other small code examples
SDCategory: Script Examples
EndScriptData */

#include "ScriptPCH.h"
#include "ScriptMgr.h"

enum eSay
{
    SAY_HI  = -1999925
};

class AT_example_areatrigger : public AreaTriggerScript
{
    public:

        AT_example_areatrigger()
            : AreaTriggerScript("example_areatrigger")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            DoScriptText(SAY_HI, player);
            return true;
        }
};

class ItemUse_example_item : public ItemScript
{
    public:

        ItemUse_example_item()
            : ItemScript("example_item")
        {
        }

        bool OnUse(Player* /*player*/, Item* /*item*/, SpellCastTargets const& /*targets*/)
        {
            sScriptMgr->LoadDatabase();
            return true;
        }
};

class GOHello_example_go_teleporter : public GameObjectScript
{
    public:

        GOHello_example_go_teleporter()
            : GameObjectScript("example_go_teleporter")
        {
        }

        bool OnGossipHello(Player* player, GameObject* /*go*/)
        {
            player->TeleportTo(0, 1807.07f, 336.105f, 70.3975f, 0.0f);
            return false;
        }
};

void AddSC_example_misc()
{
    new AT_example_areatrigger();
    new ItemUse_example_item();
    new GOHello_example_go_teleporter();
}
