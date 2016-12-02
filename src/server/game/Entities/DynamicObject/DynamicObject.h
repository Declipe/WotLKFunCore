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

#ifndef TRINITYCORE_DYNAMICOBJECT_H
#define TRINITYCORE_DYNAMICOBJECT_H

#include "Object.h"

class Unit;
class Aura;
class SpellInfo;

enum DynamicObjectType
{
    DYNAMIC_OBJECT_PORTAL           = 0x0,      // unused
    DYNAMIC_OBJECT_AREA_SPELL       = 0x1,
    DYNAMIC_OBJECT_FARSIGHT_FOCUS   = 0x2,
};

class DynamicObject : public WorldObject, public GridObject<DynamicObject>
{
    public:
        DynamicObject(bool isWorldObject);
        ~DynamicObject();

        void AddToWorld();
        void RemoveFromWorld();

        bool CreateDynamicObject(uint32 guidlow, Unit* caster, uint32 spellId, Position const& pos, float radius, DynamicObjectType type);
        void Update(uint32 p_time);
        void Remove();
        void SetDuration(int32 newDuration);
        int32 GetDuration() const;
        void Delay(int32 delaytime);
        void SetAura(Aura* aura);
        void RemoveAura();
        void SetCasterViewpoint();
        void RemoveCasterViewpoint();
        Unit* GetCaster() const { return _caster; }
        void BindToCaster();
        void UnbindFromCaster();
        uint32 GetSpellId() const {  return GetUInt32Value(DYNAMICOBJECT_SPELLID); }
        uint64 GetCasterGUID() const { return GetUInt64Value(DYNAMICOBJECT_CASTER); }
        float GetRadius() const { return GetFloatValue(DYNAMICOBJECT_RADIUS); }

        void Say(int32 textId, uint32 language, uint64 targetGuid) { MonsterSay(textId, language, targetGuid); }
        void Yell(int32 textId, uint32 language, uint64 targetGuid) { MonsterYell(textId, language, targetGuid); }
        void TextEmote(int32 textId, uint64 targetGuid) { MonsterTextEmote(textId, targetGuid); }
        void Whisper(int32 textId, uint64 receiver) { MonsterWhisper(textId, receiver); }
        void YellToZone(int32 textId, uint32 language, uint64 targetGuid) { MonsterYellToZone(textId, language, targetGuid); }

    protected:
        Aura* _aura;
        Aura* _removedAura;
        Unit* _caster;
        int32 _duration; // for non-aura dynobjects
        bool _isViewpoint;
};
#endif
