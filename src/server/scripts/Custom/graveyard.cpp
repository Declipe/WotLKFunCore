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
#include "Chat.h"
 
class graveyard : public PlayerScript
{
public:
   graveyard() : PlayerScript("graveyard") {}
 
   void OnPlayerKilledByCreature(Creature* killer, Player* killed)
   {
   if (!killed) 
	return;

          if (killed->GetMapId() == 13)
          {
    		   killed->CombatStop();
                 ChatHandler(killed).PSendSysMessage("You died, but your spirit lived on. You are as a punishment unable to act for 45 seconds.");
                 killed->TeleportTo(13, -333.884430f, -50.475521f, 626.97370f, 1.489797);
		   killer->MonsterYell("Another foolish mortal has been slain!", LANG_UNIVERSAL, NULL);
          }

          if (killer->GetEntry() == 986507)
          {
    		   killed->CombatStop();
	 	   killed->TeleportTo(34, 5541.770020f, -3783.469971f, 1594.910034f, 2.883010f);
	 	   killed->CastSpell(killed, 42354, true);
	 	   ChatHandler(killed).PSendSysMessage("You have died, and Dante has bound your soul for 45 seconds.");
    	   }

          if (killed->GetAreaId() == 255)
          {
                 ChatHandler(killed).PSendSysMessage("Emeth has destroyed your soul, you have been banished for 45 seconds.");
		   killer->MonsterYell("Another foolish mortal has been slain!", LANG_UNIVERSAL, NULL);
          }
   }
};
 
void AddSC_graveyard()
{
   new graveyard();
}