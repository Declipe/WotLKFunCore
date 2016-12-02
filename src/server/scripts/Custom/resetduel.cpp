/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
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

#include "ScriptPCH.h"

class Reset_OnDuelEnd : public PlayerScript
{
    public:
        Reset_OnDuelEnd() : PlayerScript("Reset_OnDuelEnd") {}

    void OnDuelEnd(Player *winner, Player *looser, DuelCompleteType type)
    {
                        winner->GetSession()->SendNotification("You just defeated %s! in a duel!", looser->GetName());
                        winner->RemoveArenaSpellCooldowns();
                        winner->SetHealth(winner->GetMaxHealth());
                        looser->GetSession()->SendNotification("%s defeated you in a duel!", winner->GetName());
                        looser->SetHealth(looser->GetMaxHealth());
	                 if (winner->getPowerType() == POWER_MANA) 
       	          	winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));
            		   if (looser->getPowerType() == POWER_MANA) 
                	   	looser->SetPower(POWER_MANA, looser->GetMaxPower(POWER_MANA));
    }
};

void AddSC_Reset()
{
    new Reset_OnDuelEnd;
}
