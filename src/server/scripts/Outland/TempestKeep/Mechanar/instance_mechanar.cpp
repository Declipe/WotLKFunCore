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
SDName: Instance_Mechanar
SD%Complete: 100
SDComment:
SDCategory: Mechanar
EndScriptData */

#include "ScriptPCH.h"
#include "mechanar.h"

#define MAX_ENCOUNTER      1

class instance_mechanar : public InstanceMapScript
{
    public:
        instance_mechanar()
            : InstanceMapScript("instance_mechanar", 554)
        {
        }

        struct instance_mechanar_InstanceMapScript : public InstanceScript
        {
            instance_mechanar_InstanceMapScript(Map* map) : InstanceScript(map) {}

            uint32 m_auiEncounter[MAX_ENCOUNTER];

            void Initialize()
            {
                memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
            }

            bool IsEncounterInProgress() const
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (m_auiEncounter[i] == IN_PROGRESS)
                        return true;

                return false;
            }

            uint32 GetData(uint32 type)
            {
                switch (type)
                {
                case DATA_NETHERMANCER_EVENT:   return m_auiEncounter[0];
                }

                return false;
            }

            uint64 GetData64(uint32 /*identifier*/)
            {
                return 0;
            }

            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
                case DATA_NETHERMANCER_EVENT:   m_auiEncounter[0] = data;   break;
                }
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_mechanar_InstanceMapScript(map);
        }
};

void AddSC_instance_mechanar()
{
    new instance_mechanar;
}

