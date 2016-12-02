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
SDName: Boss_Renataki
SD%Complete: 100
SDComment:
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptPCH.h"
#include "zulgurub.h"

#define SPELL_AMBUSH            24337
#define SPELL_THOUSANDBLADES    24649

#define EQUIP_ID_MAIN_HAND      0           //was item display id 31818, but this id does not exist

class boss_renataki : public CreatureScript
{
    public:

        boss_renataki()
            : CreatureScript("boss_renataki")
        {
        }

        struct boss_renatakiAI : public ScriptedAI
        {
            boss_renatakiAI(Creature* creature) : ScriptedAI(creature) {}

            uint32 Invisible_Timer;
            uint32 Ambush_Timer;
            uint32 Visible_Timer;
            uint32 Aggro_Timer;
            uint32 ThousandBlades_Timer;

            bool Invisible;
            bool Ambushed;

            void Reset()
            {
                Invisible_Timer = urand(8000, 18000);
                Ambush_Timer = 3000;
                Visible_Timer = 4000;
                Aggro_Timer = urand(15000, 25000);
                ThousandBlades_Timer = urand(4000, 8000);

                Invisible = false;
                Ambushed = false;
            }

            void EnterCombat(Unit* /*who*/)
            {
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                //Invisible_Timer
                if (Invisible_Timer <= diff)
                {
                    me->InterruptSpell(CURRENT_GENERIC_SPELL);

                    SetEquipmentSlots(false, EQUIP_UNEQUIP, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE);
                    me->SetDisplayId(11686);

                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    Invisible = true;

                    Invisible_Timer = urand(15000, 30000);
                } else Invisible_Timer -= diff;

                if (Invisible)
                {
                    if (Ambush_Timer <= diff)
                    {
                        Unit* target = NULL;
                        target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                        if (target)
                        {
                            DoTeleportTo(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
                            DoCast(target, SPELL_AMBUSH);
                        }

                        Ambushed = true;
                        Ambush_Timer = 3000;
                    } else Ambush_Timer -= diff;
                }

                if (Ambushed)
                {
                    if (Visible_Timer <= diff)
                    {
                        me->InterruptSpell(CURRENT_GENERIC_SPELL);

                        me->SetDisplayId(15268);
                        SetEquipmentSlots(false, EQUIP_ID_MAIN_HAND, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE);

                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        Invisible = false;

                        Visible_Timer = 4000;
                    } else Visible_Timer -= diff;
                }

                //Resetting some aggro so he attacks other gamers
                if (!Invisible)
                {
                    if (Aggro_Timer <= diff)
                    {
                        Unit* target = NULL;
                        target = SelectTarget(SELECT_TARGET_RANDOM, 1);

                        if (DoGetThreat(me->getVictim()))
                            DoModifyThreatPercent(me->getVictim(), -50);

                        if (target)
                            AttackStart(target);

                        Aggro_Timer = urand(7000, 20000);
                    } else Aggro_Timer -= diff;

                    if (ThousandBlades_Timer <= diff)
                    {
                        DoCast(me->getVictim(), SPELL_THOUSANDBLADES);
                        ThousandBlades_Timer = urand(7000, 12000);
                    } else ThousandBlades_Timer -= diff;
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_renatakiAI(creature);
        }
};

void AddSC_boss_renataki()
{
    new boss_renataki();
}

