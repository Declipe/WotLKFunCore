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
SDName: Arathi Highlands
SD%Complete: 100
SDComment: Quest support: 665
SDCategory: Arathi Highlands
EndScriptData */

/* ContentData
npc_professor_phizzlethorpe
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

/*######
## npc_professor_phizzlethorpe
######*/

enum eEnums
{
    SAY_PROGRESS_1      = 0,
    SAY_PROGRESS_2      = 1,
    SAY_PROGRESS_3      = 2,
    EMOTE_PROGRESS_4    = 3,
    SAY_AGGRO           = 4,
    SAY_PROGRESS_5      = 5,
    SAY_PROGRESS_6      = 6,
    SAY_PROGRESS_7      = 7,
    EMOTE_PROGRESS_8    = 8,
    SAY_PROGRESS_9      = 9,

    QUEST_SUNKEN_TREASURE   = 665,
    MOB_VENGEFUL_SURGE      = 2776
};

class npc_professor_phizzlethorpe : public CreatureScript
{
    public:

        npc_professor_phizzlethorpe()
            : CreatureScript("npc_professor_phizzlethorpe")
        {
        }

        struct npc_professor_phizzlethorpeAI : public npc_escortAI
        {
            npc_professor_phizzlethorpeAI(Creature* creature) : npc_escortAI(creature) {}

            void WaypointReached(uint32 waypointId)
            {
                Player* player = GetPlayerForEscort();
                if (!player)
                    return;

                switch (waypointId)
                {
                    case 4:
                        Talk(SAY_PROGRESS_2, player->GetGUID());
                        break;
                    case 5:
                        Talk(SAY_PROGRESS_3, player->GetGUID());
                        break;
                    case 8:
                        Talk(EMOTE_PROGRESS_4);
                        break;
                    case 9:
                        me->SummonCreature(MOB_VENGEFUL_SURGE, -2052.96f, -2142.49f, 20.15f, 1.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);
                        me->SummonCreature(MOB_VENGEFUL_SURGE, -2052.96f, -2142.49f, 20.15f, 1.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);
                        break;
                    case 10:
                        Talk(SAY_PROGRESS_5, player->GetGUID());
                        break;
                    case 11:
                        Talk(SAY_PROGRESS_6, player->GetGUID());
                        SetRun();
                        break;
                    case 19:
                        Talk(SAY_PROGRESS_7, player->GetGUID());
                        break;
                    case 20:
                        Talk(EMOTE_PROGRESS_8);
                        Talk(SAY_PROGRESS_9, player->GetGUID());
                        player->GroupEventHappens(QUEST_SUNKEN_TREASURE, me);
                        break;
                }
            }

            void JustSummoned(Creature* summoned)
            {
                summoned->AI()->AttackStart(me);
            }

            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_AGGRO);
            }

            void UpdateAI(const uint32 diff)
            {
                npc_escortAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_professor_phizzlethorpeAI(creature);
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_SUNKEN_TREASURE)
            {
                creature->AI()->Talk(SAY_PROGRESS_1, player->GetGUID());
                if (npc_escortAI* pEscortAI = CAST_AI(npc_professor_phizzlethorpeAI, (creature->AI())))
                    pEscortAI->Start(false, false, player->GetGUID(), quest);

                creature->setFaction(113);
            }
            return true;
        }
};

void AddSC_arathi_highlands()
{
    new npc_professor_phizzlethorpe();
}
