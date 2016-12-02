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
SDName: Instance_Hellfire_Ramparts
SD%Complete: 50
SDComment:
SDCategory: Hellfire Ramparts
EndScriptData */

#include "ScriptPCH.h"
#include "hellfire_ramparts.h"

class instance_ramparts : public InstanceMapScript
{
    public:
        instance_ramparts()
            : InstanceMapScript("instance_ramparts", 543)
        {
        }

        struct instance_ramparts_InstanceMapScript : public InstanceScript
        {
            instance_ramparts_InstanceMapScript(Map* map) : InstanceScript(map) {}

            uint32 m_auiEncounter[MAX_ENCOUNTER];
            uint64 m_uiChestNGUID;
            uint64 m_uiChestHGUID;
            bool spawned;

            void Initialize()
            {
                memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

                m_uiChestNGUID = 0;
                m_uiChestHGUID = 0;
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case 185168:
                        m_uiChestNGUID = go->GetGUID();
                        break;
                    case 185169:
                        m_uiChestHGUID = go->GetGUID();
                        break;
                }
            }

            void SetData(uint32 uiType, uint32 uiData)
            {
                sLog->outDebug(LOG_FILTER_TSCR, "TSCR: Instance Ramparts: SetData received for type %u with data %u", uiType, uiData);

                switch (uiType)
                {
                    case TYPE_VAZRUDEN:
                        if (uiData == DONE && m_auiEncounter[1] == DONE && !spawned)
                        {
                            DoRespawnGameObject(instance->IsHeroic() ? m_uiChestHGUID : m_uiChestNGUID, HOUR*IN_MILLISECONDS);
                            spawned = true;
                        }
                        m_auiEncounter[0] = uiData;
                        break;
                    case TYPE_NAZAN:
                        if (uiData == DONE && m_auiEncounter[0] == DONE && !spawned)
                        {
                            DoRespawnGameObject(instance->IsHeroic() ? m_uiChestHGUID : m_uiChestNGUID, HOUR*IN_MILLISECONDS);
                            spawned = true;
                        }
                        m_auiEncounter[1] = uiData;
                        break;
                }
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_ramparts_InstanceMapScript(map);
        }
};

void AddSC_instance_ramparts()
{
    new instance_ramparts;
}
