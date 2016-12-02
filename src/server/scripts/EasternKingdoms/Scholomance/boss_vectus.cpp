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
SDName: Boss_Vectus
SD%Complete: 100
SDComment:
SDCategory: Scholomance
EndScriptData */

#include "ScriptPCH.h"

enum eEnums
{
    SPELL_FLAMESTRIKE            = 18399,
    SPELL_BLAST_WAVE             = 16046,
    SPELL_FIRESHIELD             = 19626,
    SPELL_FRENZY                 = 8269 //28371,
};

class boss_vectus : public CreatureScript
{
public:
    boss_vectus() : CreatureScript("boss_vectus") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_vectusAI (creature);
    }

    struct boss_vectusAI : public ScriptedAI
    {
        boss_vectusAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 m_uiFireShield_Timer;
        uint32 m_uiBlastWave_Timer;
        uint32 m_uiFrenzy_Timer;

        void Reset()
        {
            m_uiFireShield_Timer = 2000;
            m_uiBlastWave_Timer = 14000;
            m_uiFrenzy_Timer = 0;
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            //FireShield_Timer
            if (m_uiFireShield_Timer <= uiDiff)
            {
                DoCast(me, SPELL_FIRESHIELD);
                m_uiFireShield_Timer = 90000;
            }
            else
                m_uiFireShield_Timer -= uiDiff;

            //BlastWave_Timer
            if (m_uiBlastWave_Timer <= uiDiff)
            {
                DoCast(me->getVictim(), SPELL_BLAST_WAVE);
                m_uiBlastWave_Timer = 12000;
            }
            else
                m_uiBlastWave_Timer -= uiDiff;

            //Frenzy_Timer
            if (HealthBelowPct(25))
            {
                if (m_uiFrenzy_Timer <= uiDiff)
                {
                    DoCast(me, SPELL_FRENZY);
                    DoScriptText(EMOTE_GENERIC_FRENZY_KILL, me);

                    m_uiFrenzy_Timer = 24000;
                }
                else
                    m_uiFrenzy_Timer -= uiDiff;
            }

            DoMeleeAttackIfReady();
        }
    };

};

void AddSC_boss_vectus()
{
    new boss_vectus();
}
