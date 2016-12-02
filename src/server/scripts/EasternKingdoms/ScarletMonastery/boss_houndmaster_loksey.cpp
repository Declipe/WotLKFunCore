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
SDName: Boss_Houndmaster_Loksey
SD%Complete: 100
SDComment:
SDCategory: Scarlet Monastery
EndScriptData */

#include "ScriptPCH.h"

enum eEnums
{
    SAY_AGGRO                       = -1189021,
    SPELL_SUMMONSCARLETHOUND        = 17164,
    SPELL_BLOODLUST                 = 6742
};

class boss_houndmaster_loksey : public CreatureScript
{
public:
    boss_houndmaster_loksey() : CreatureScript("boss_houndmaster_loksey") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_houndmaster_lokseyAI (creature);
    }

    struct boss_houndmaster_lokseyAI : public ScriptedAI
    {
        boss_houndmaster_lokseyAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 BloodLust_Timer;

        void Reset()
        {
            BloodLust_Timer = 20000;
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (BloodLust_Timer <= diff)
            {
                DoCast(me, SPELL_BLOODLUST);
                BloodLust_Timer = 20000;
            }
            else BloodLust_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_houndmaster_loksey()
{
    new boss_houndmaster_loksey();
}
