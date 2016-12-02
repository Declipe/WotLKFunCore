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

#ifndef TRINITY_CREATUREAIFACTORY_H
#define TRINITY_CREATUREAIFACTORY_H

//#include "Policies/Singleton.h"
#include "ObjectRegistry.h"
#include "FactoryHolder.h"
#include "GameObjectAI.h"

struct SelectableAI : public FactoryHolder<CreatureAI>, public Permissible<Creature>
{
    SelectableAI(const char* id) : FactoryHolder<CreatureAI>(id) {}
};

template<class REAL_AI>
struct CreatureAIFactory : public SelectableAI
{
    CreatureAIFactory(const char* name) : SelectableAI(name) {}

    CreatureAI* Create(void*) const;

    int Permit(const Creature* c) const { return REAL_AI::Permissible(c); }
};

template<class REAL_AI>
inline CreatureAI*
CreatureAIFactory<REAL_AI>::Create(void* data) const
{
    Creature* creature = reinterpret_cast<Creature*>(data);
    return (new REAL_AI(creature));
}

typedef FactoryHolder<CreatureAI> CreatureAICreator;
typedef FactoryHolder<CreatureAI>::FactoryHolderRegistry CreatureAIRegistry;
typedef FactoryHolder<CreatureAI>::FactoryHolderRepository CreatureAIRepository;

//GO
struct SelectableGameObjectAI : public FactoryHolder<GameObjectAI>, public Permissible<GameObject>
{
    SelectableGameObjectAI(const char* id) : FactoryHolder<GameObjectAI>(id) {}
};

template<class REAL_GO_AI>
struct GameObjectAIFactory : public SelectableGameObjectAI
{
    GameObjectAIFactory(const char* name) : SelectableGameObjectAI(name) {}

    GameObjectAI* Create(void*) const;

    int Permit(const GameObject* g) const { return REAL_GO_AI::Permissible(g); }
};

template<class REAL_GO_AI>
inline GameObjectAI*
GameObjectAIFactory<REAL_GO_AI>::Create(void* data) const
{
    GameObject* go = reinterpret_cast<GameObject*>(data);
    return (new REAL_GO_AI(go));
}

typedef FactoryHolder<GameObjectAI> GameObjectAICreator;
typedef FactoryHolder<GameObjectAI>::FactoryHolderRegistry GameObjectAIRegistry;
typedef FactoryHolder<GameObjectAI>::FactoryHolderRepository GameObjectAIRepository;
#endif
