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

#ifndef TRINITYCORE_TEMPSUMMON_H
#define TRINITYCORE_TEMPSUMMON_H

#include "Creature.h"

class TempSummon : public Creature
{
    public:
        explicit TempSummon(SummonPropertiesEntry const* properties, Unit* owner, bool isWorldObject);
        virtual ~TempSummon() {}
        void Update(uint32 time);
        virtual void InitStats(uint32 lifetime);
        virtual void InitSummon();
        void UnSummon(uint32 msTime = 0);
        void RemoveFromWorld();
        void SetTempSummonType(TempSummonType type);
        void SaveToDB(uint32 /*mapid*/, uint8 /*spawnMask*/, uint32 /*phaseMask*/) {}
        Unit* GetSummoner() const;
        uint64 GetSummonerGUID() { return m_summonerGUID; }
        TempSummonType const& GetSummonType() { return m_type; }

        const SummonPropertiesEntry* const m_Properties;
    private:
        TempSummonType m_type;
        uint32 m_timer;
        uint32 m_lifetime;
        uint64 m_summonerGUID;
};

class Minion : public TempSummon
{
    public:
        Minion(SummonPropertiesEntry const* properties, Unit* owner, bool isWorldObject);
        void InitStats(uint32 duration);
        void RemoveFromWorld();
        Unit* GetOwner() { return m_owner; }
        float GetFollowAngle() const { return m_followAngle; }
        void SetFollowAngle(float angle) { m_followAngle = angle; }
        bool IsPetGhoul() const {return GetEntry() == 26125;} // Ghoul may be guardian or pet
        bool IsGuardianPet() const;
    protected:
        Unit* const m_owner;
        float m_followAngle;
};

class Guardian : public Minion
{
    public:
        Guardian(SummonPropertiesEntry const* properties, Unit* owner, bool isWorldObject);
        void InitStats(uint32 duration);
        bool InitStatsForLevel(uint8 level);
        void InitSummon();

        bool UpdateStats(Stats stat);
        bool UpdateAllStats();
        void UpdateResistances(uint32 school);
        void UpdateArmor();
        void UpdateMaxHealth();
        void UpdateMaxPower(Powers power);
        void UpdateAttackPowerAndDamage(bool ranged = false);
        void UpdateDamagePhysical(WeaponAttackType attType);

        int32 GetBonusDamage() { return m_bonusSpellDamage; }
        void SetBonusDamage(int32 damage);
    protected:
        int32   m_bonusSpellDamage;
        float   m_statFromOwner[MAX_STATS];
};

class Puppet : public Minion
{
    public:
        Puppet(SummonPropertiesEntry const* properties, Unit* owner);
        void InitStats(uint32 duration);
        void InitSummon();
        void Update(uint32 time);
        void RemoveFromWorld();
    protected:
        Player* m_owner;
};

class ForcedUnsummonDelayEvent : public BasicEvent
{
public:
    ForcedUnsummonDelayEvent(TempSummon& owner) : BasicEvent(), m_owner(owner) { }
    bool Execute(uint64 e_time, uint32 p_time);

private:
    TempSummon& m_owner;
};
#endif
