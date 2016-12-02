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
SDName: Instance_Shadowfang_Keep
SD%Complete: 90
SDComment:
SDCategory: Shadowfang Keep
EndScriptData */

#include "ScriptPCH.h"
#include "shadowfang_keep.h"

#define MAX_ENCOUNTER              4

enum eEnums
{
    SAY_BOSS_DIE_AD         = -1033007,
    SAY_BOSS_DIE_AS         = -1033008,
    SAY_ARCHMAGE            = -1033009,

    NPC_ASH                 = 3850,
    NPC_ADA                 = 3849,
    NPC_ARCHMAGE_ARUGAL     = 4275,
    NPC_ARUGAL_VOIDWALKER   = 4627,

    GO_COURTYARD_DOOR       = 18895,                        //door to open when talking to NPC's
    GO_SORCERER_DOOR        = 18972,                        //door to open when Fenrus the Devourer
    GO_ARUGAL_DOOR          = 18971,                        //door to open when Wolf Master Nandos

    SPELL_ASHCROMBE_TELEPORT    = 15742
};

const Position SpawnLocation[] =
{
    {-148.199f, 2165.647f, 128.448f, 1.026f},
    {-153.110f, 2168.620f, 128.448f, 1.026f},
    {-145.905f, 2180.520f, 128.448f, 4.183f},
    {-140.794f, 2178.037f, 128.448f, 4.090f},
    {-138.640f, 2170.159f, 136.577f, 2.737f}
};
class instance_shadowfang_keep : public InstanceMapScript
{
public:
    instance_shadowfang_keep() : InstanceMapScript("instance_shadowfang_keep", 33) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_shadowfang_keep_InstanceMapScript(map);
    }

    struct instance_shadowfang_keep_InstanceMapScript : public InstanceScript
    {
        instance_shadowfang_keep_InstanceMapScript(Map* map) : InstanceScript(map) {}

        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string str_data;

        uint64 uiAshGUID;
        uint64 uiAdaGUID;
        uint64 uiArchmageArugalGUID;

        uint64 DoorCourtyardGUID;
        uint64 DoorSorcererGUID;
        uint64 DoorArugalGUID;

        uint8 uiPhase;
        uint16 uiTimer;

        void Initialize()
        {
            memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

            uiAshGUID = 0;
            uiAdaGUID = 0;
            uiArchmageArugalGUID = 0;

            DoorCourtyardGUID = 0;
            DoorSorcererGUID = 0;
            DoorArugalGUID = 0;

            uiPhase = 0;
            uiTimer = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case NPC_ASH: uiAshGUID = creature->GetGUID(); break;
                case NPC_ADA: uiAdaGUID = creature->GetGUID(); break;
                case NPC_ARCHMAGE_ARUGAL: uiArchmageArugalGUID = creature->GetGUID(); break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_COURTYARD_DOOR:
                    DoorCourtyardGUID = go->GetGUID();
                    if (m_auiEncounter[0] == DONE)
                        HandleGameObject(0, true, go);
                    break;
                case GO_SORCERER_DOOR:
                    DoorSorcererGUID = go->GetGUID();
                    if (m_auiEncounter[2] == DONE)
                        HandleGameObject(0, true, go);
                    break;
                case GO_ARUGAL_DOOR:
                    DoorArugalGUID = go->GetGUID();
                    if (m_auiEncounter[3] == DONE)
                        HandleGameObject(0, true, go);
                    break;
            }
        }

        void DoSpeech()
        {
            Creature* pAda = instance->GetCreature(uiAdaGUID);
            Creature* pAsh = instance->GetCreature(uiAshGUID);

            if (pAda && pAda->isAlive() && pAsh && pAsh->isAlive())
            {
                DoScriptText(SAY_BOSS_DIE_AD, pAda);
                DoScriptText(SAY_BOSS_DIE_AS, pAsh);
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case TYPE_FREE_NPC:
                    if (data == DONE)
                        DoUseDoorOrButton(DoorCourtyardGUID);
                    m_auiEncounter[0] = data;
                    break;
                case TYPE_RETHILGORE:
                    if (data == DONE)
                        DoSpeech();
                    m_auiEncounter[1] = data;
                    break;
                case TYPE_FENRUS:
                    switch (data)
                    {
                        case DONE:
                            uiTimer = 1000;
                            uiPhase = 1;
                            break;
                        case 7:
                            DoUseDoorOrButton(DoorSorcererGUID);
                            break;
                    }
                    m_auiEncounter[2] = data;
                    break;
                case TYPE_NANDOS:
                    if (data == DONE)
                        DoUseDoorOrButton(DoorArugalGUID);
                    m_auiEncounter[3] = data;
                    break;
            }

            if (data == DONE)
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << m_auiEncounter[0] << ' ' << m_auiEncounter[1] << ' ' << m_auiEncounter[2] << ' ' << m_auiEncounter[3];

                str_data = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        uint32 GetData(uint32 type)
        {
            switch (type)
            {
                case TYPE_FREE_NPC:
                    return m_auiEncounter[0];
                case TYPE_RETHILGORE:
                    return m_auiEncounter[1];
                case TYPE_FENRUS:
                    return m_auiEncounter[2];
                case TYPE_NANDOS:
                    return m_auiEncounter[3];
            }
            return 0;
        }

        std::string GetSaveData()
        {
            return str_data;
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            std::istringstream loadStream(in);
            loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3];

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                if (m_auiEncounter[i] == IN_PROGRESS)
                    m_auiEncounter[i] = NOT_STARTED;
            }

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void Update(uint32 uiDiff)
        {
            if (GetData(TYPE_FENRUS) != DONE)
                return;

            Creature* pArchmage = instance->GetCreature(uiArchmageArugalGUID);
            Creature* summon = NULL;

            if (!pArchmage || !pArchmage->isAlive())
                return;

            if (uiPhase)
            {
                if (uiTimer <= uiDiff)
                {
                    switch (uiPhase)
                    {
                        case 1:
                            summon = pArchmage->SummonCreature(pArchmage->GetEntry(), SpawnLocation[4], TEMPSUMMON_TIMED_DESPAWN, 10000);
                            summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                            summon->SetReactState(REACT_DEFENSIVE);
                            summon->CastSpell(summon, SPELL_ASHCROMBE_TELEPORT, true);
                            DoScriptText(SAY_ARCHMAGE, summon);
                            uiTimer = 2000;
                            uiPhase = 2;
                            break;
                        case 2:
                            pArchmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[0], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                            pArchmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[1], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                            pArchmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[2], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                            pArchmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                            uiPhase = 0;
                            break;

                    }
                } else uiTimer -= uiDiff;
            }
        }
    };

};

void AddSC_instance_shadowfang_keep()
{
    new instance_shadowfang_keep();
}
