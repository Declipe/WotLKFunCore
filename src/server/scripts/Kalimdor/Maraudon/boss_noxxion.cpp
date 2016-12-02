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
SDName: Boss_Noxxion
SD%Complete: 100
SDComment:
SDCategory: Maraudon
EndScriptData */

#include "ScriptPCH.h"
enum Spells
{
    SPELL_TOXICVOLLEY           = 21687,
    SPELL_UPPERCUT              = 22916
};

class boss_noxxion : public CreatureScript
{
public:
    boss_noxxion() : CreatureScript("boss_noxxion") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_noxxionAI (creature);
    }

    struct boss_noxxionAI : public ScriptedAI
    {
        boss_noxxionAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 ToxicVolley_Timer;
        uint32 Uppercut_Timer;
        uint32 Adds_Timer;
        uint32 Invisible_Timer;
        bool Invisible;

        void Reset()
        {
            ToxicVolley_Timer = 7000;
            Uppercut_Timer = 16000;
            Adds_Timer = 19000;
            Invisible_Timer = 15000;                            //Too much too low?
            Invisible = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void SummonAdds(Unit* victim)
        {
            if (Creature* Add = DoSpawnCreature(13456, float(irand(-7, 7)), float(irand(-7, 7)), 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 90000))
                Add->AI()->AttackStart(victim);
        }

        void UpdateAI(const uint32 diff)
        {
            if (Invisible && Invisible_Timer <= diff)
            {
                //Become visible again
                me->setFaction(14);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                //Noxxion model
                me->SetDisplayId(11172);
                Invisible = false;
                //me->m_canMove = true;
            }
            else if (Invisible)
            {
                Invisible_Timer -= diff;
                //Do nothing while invisible
                return;
            }

            //Return since we have no target
            if (!UpdateVictim())
                return;

            //ToxicVolley_Timer
            if (ToxicVolley_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_TOXICVOLLEY);
                ToxicVolley_Timer = 9000;
            }
            else ToxicVolley_Timer -= diff;

            //Uppercut_Timer
            if (Uppercut_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_UPPERCUT);
                Uppercut_Timer = 12000;
            }
            else Uppercut_Timer -= diff;

            //Adds_Timer
            if (!Invisible && Adds_Timer <= diff)
            {
                //Interrupt any spell casting
                //me->m_canMove = true;
                me->InterruptNonMeleeSpells(false);
                me->setFaction(35);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                // Invisible Model
                me->SetDisplayId(11686);
                SummonAdds(me->getVictim());
                SummonAdds(me->getVictim());
                SummonAdds(me->getVictim());
                SummonAdds(me->getVictim());
                SummonAdds(me->getVictim());
                Invisible = true;
                Invisible_Timer = 15000;

                Adds_Timer = 40000;
            }
            else Adds_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_noxxion()
{
    new boss_noxxion();
}
