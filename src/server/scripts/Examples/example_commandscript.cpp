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
Name: Example_Commandscript
%Complete: 100
Comment: Short custom scripting example
Category: Script Examples
EndScriptData */

#include "ScriptPCH.h"
#include "Chat.h"

// **** This script is designed as an example for others to build on ****
// **** Please modify whatever you'd like to as this script is only for developement ****

// **** Script Info* ***
// This script's primary purpose is to show just how much you can really do with commandscripts

class example_commandscript : public CommandScript
{
    public:
        example_commandscript() : CommandScript("example_commandscript") { }

        static bool HandleHelloWorldCommand(ChatHandler* handler, const char* /*args*/)
        {
            handler->PSendSysMessage("Hello World");
            return true;
        }

        ChatCommand* GetCommands() const
        {
            static ChatCommand HelloWorldCommandTable[] =
            {
                { "hello",          SEC_PLAYER,         true,   &HandleHelloWorldCommand,        "", NULL },
                { NULL,             0,                  false,  NULL,                            "", NULL }
            };
            return HelloWorldCommandTable;
        }
};

void AddSC_example_commandscript()
{
    new example_commandscript();
}
