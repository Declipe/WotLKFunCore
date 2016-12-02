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
SDName: Instance_Shattered_Halls
SD%Complete: 50
SDComment: currently missing info about door. instance not complete
SDCategory: Hellfire Citadel, Shattered Halls
EndScriptData */

#include "ScriptPCH.h"
#include "shattered_halls.h"

#define MAX_ENCOUNTER  2

#define DOOR_NETHEKURSE     1

class instance_shattered_halls : public InstanceMapScript
{
    public:
        instance_shattered_halls()
            : InstanceMapScript("instance_shattered_halls", 540)
        {
        }
        struct instance_shattered_halls_InstanceMapScript : public InstanceScript
        {
            instance_shattered_halls_InstanceMapScript(Map* map) : InstanceScript(map) {}

            uint32 m_auiEncounter[MAX_ENCOUNTER];
            uint64 nethekurseGUID;
            uint64 nethekurseDoorGUID;

            void Initialize()
            {
                memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

                nethekurseGUID = 0;
                nethekurseDoorGUID = 0;
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case DOOR_NETHEKURSE:
                        nethekurseDoorGUID = go->GetGUID();
                        break;
                }
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case 16807:
                        nethekurseGUID = creature->GetGUID();
                        break;
                }
            }

            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
                    case TYPE_NETHEKURSE:
                        m_auiEncounter[0] = data;
                        break;
                    case TYPE_OMROGG:
                        m_auiEncounter[1] = data;
                        break;
                }
            }

            uint32 GetData(uint32 type)
            {
                switch (type)
                {
                    case TYPE_NETHEKURSE:
                        return m_auiEncounter[0];
                    case TYPE_OMROGG:
                        return m_auiEncounter[1];
                }
                return 0;
            }

            uint64 GetData64(uint32 data)
            {
                switch (data)
                {
                    case DATA_NETHEKURSE:
                        return nethekurseGUID;
                    case DATA_NETHEKURSE_DOOR:
                        return nethekurseDoorGUID;
                }
                return 0;
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_shattered_halls_InstanceMapScript(map);
        }
};

void AddSC_instance_shattered_halls()
{
    new instance_shattered_halls();
}

