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
SDName: Instance_ZulGurub
SD%Complete: 80
SDComment: Missing reset function after killing a boss for Ohgan, Thekal.
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptPCH.h"
#include "zulgurub.h"

class instance_zulgurub : public InstanceMapScript
{
    public:
        instance_zulgurub()
            : InstanceMapScript("instance_zulgurub", 309)
        {
        }

        struct instance_zulgurub_InstanceMapScript : public InstanceScript
        {
            instance_zulgurub_InstanceMapScript(Map* map) : InstanceScript(map) {}

            //If all High Priest bosses were killed. Lorkhan, Zath and Ohgan are added too.
            uint32 m_auiEncounter[MAX_ENCOUNTERS];

            //Storing Lorkhan, Zath and Thekal because we need to cast on them later. Jindo is needed for healfunction too.
            uint64 m_uiLorKhanGUID;
            uint64 m_uiZathGUID;
            uint64 m_uiThekalGUID;
            uint64 m_uiJindoGUID;

            void Initialize()
            {
                memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

                m_uiLorKhanGUID = 0;
                m_uiZathGUID = 0;
                m_uiThekalGUID = 0;
                m_uiJindoGUID = 0;
            }

            bool IsEncounterInProgress() const
            {
                //not active in Zul'Gurub
                return false;
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case 11347: m_uiLorKhanGUID = creature->GetGUID(); break;
                    case 11348: m_uiZathGUID = creature->GetGUID(); break;
                    case 14509: m_uiThekalGUID = creature->GetGUID(); break;
                    case 11380: m_uiJindoGUID = creature->GetGUID(); break;
                }
            }

            void SetData(uint32 uiType, uint32 uiData)
            {
                switch (uiType)
                {
                    case DATA_ARLOKK:
                        m_auiEncounter[0] = uiData;
                        break;

                    case DATA_JEKLIK:
                        m_auiEncounter[1] = uiData;
                        break;

                    case DATA_VENOXIS:
                        m_auiEncounter[2] = uiData;
                        break;

                    case DATA_MARLI:
                        m_auiEncounter[3] = uiData;
                        break;

                    case DATA_THEKAL:
                        m_auiEncounter[4] = uiData;
                        break;

                    case DATA_LORKHAN:
                        m_auiEncounter[5] = uiData;
                        break;

                    case DATA_ZATH:
                        m_auiEncounter[6] = uiData;
                        break;

                    case DATA_OHGAN:
                        m_auiEncounter[7] = uiData;
                        break;
                }
            }

            uint32 GetData(uint32 uiType)
            {
                switch (uiType)
                {
                    case DATA_ARLOKK:
                        return m_auiEncounter[0];
                    case DATA_JEKLIK:
                        return m_auiEncounter[1];
                    case DATA_VENOXIS:
                        return m_auiEncounter[2];
                    case DATA_MARLI:
                        return m_auiEncounter[3];
                    case DATA_THEKAL:
                        return m_auiEncounter[4];
                    case DATA_LORKHAN:
                        return m_auiEncounter[5];
                    case DATA_ZATH:
                        return m_auiEncounter[6];
                    case DATA_OHGAN:
                        return m_auiEncounter[7];
                }
                return 0;
            }

            uint64 GetData64(uint32 uiData)
            {
                switch (uiData)
                {
                    case DATA_LORKHAN:
                        return m_uiLorKhanGUID;
                    case DATA_ZATH:
                        return m_uiZathGUID;
                    case DATA_THEKAL:
                        return m_uiThekalGUID;
                    case DATA_JINDO:
                        return m_uiJindoGUID;
                }
                return 0;
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_zulgurub_InstanceMapScript(map);
        }
};

void AddSC_instance_zulgurub()
{
    new instance_zulgurub();
}