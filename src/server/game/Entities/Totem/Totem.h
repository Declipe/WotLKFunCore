/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2005-2016 MaNGOS.
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

#ifndef TRINITYCORE_TOTEM_H
#define TRINITYCORE_TOTEM_H

#include "TemporarySummon.h"

enum TotemType
{
    TOTEM_PASSIVE    = 0,
    TOTEM_ACTIVE     = 1,
    TOTEM_STATUE     = 2 // copied straight from MaNGOS, may need more implementation to work
};

#define SENTRY_TOTEM_ENTRY  3968

class Totem : public Minion
{
    public:
        Totem(SummonPropertiesEntry const* properties, Unit* owner);
        virtual ~Totem() {}
        void Update(uint32 time);
        void InitStats(uint32 duration);
        void InitSummon();
        void UnSummon();
        uint32 GetSpell(uint8 slot = 0) const { return m_spells[slot]; }
        uint32 GetTotemDuration() const { return m_duration; }
        void SetTotemDuration(uint32 duration) { m_duration = duration; }
        TotemType GetTotemType() const { return m_type; }

        bool UpdateStats(Stats /*stat*/) { return true; }
        bool UpdateAllStats() { return true; }
        void UpdateResistances(uint32 /*school*/) {}
        void UpdateArmor() {}
        void UpdateMaxHealth() {}
        void UpdateMaxPower(Powers /*power*/) {}
        void UpdateAttackPowerAndDamage(bool /*ranged*/) {}
        void UpdateDamagePhysical(WeaponAttackType /*attType*/) {}

        bool IsImmunedToSpellEffect(SpellInfo const* spellInfo, uint32 index) const;

    protected:
        TotemType m_type;
        uint32 m_duration;
};
#endif
