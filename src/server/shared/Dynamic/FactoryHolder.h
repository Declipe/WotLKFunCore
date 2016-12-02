/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2006-2016 MaNGOS.
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

#ifndef TRINITY_FACTORY_HOLDER
#define TRINITY_FACTORY_HOLDER

#include "Define.h"
#include "Dynamic/TypeList.h"
#include "ObjectRegistry.h"

/** FactoryHolder holds a factory object of a specific type
 */
template<class T, class Key = std::string>
class FactoryHolder
{
    public:
        typedef ObjectRegistry<FactoryHolder<T, Key >, Key > FactoryHolderRegistry;
        friend class ACE_Singleton<FactoryHolderRegistry, ACE_Null_Mutex>;
        typedef ACE_Singleton<FactoryHolderRegistry, ACE_Null_Mutex> FactoryHolderRepository;

        FactoryHolder(Key k) : i_key(k) {}
        virtual ~FactoryHolder() {}
        inline Key key() const { return i_key; }

        void RegisterSelf(void) { FactoryHolderRepository::instance()->InsertItem(this, i_key); }
        void DeregisterSelf(void) { FactoryHolderRepository::instance()->RemoveItem(this, false); }

        /// Abstract Factory create method
        virtual T* Create(void *data = NULL) const = 0;
    private:
        Key i_key;
};

/** Permissible is a classic way of letting the object decide
 * whether how good they handle things.  This is not retricted
 * to factory selectors.
 */
template<class T>
class Permissible
{
    public:
        virtual ~Permissible() {}
        virtual int Permit(const T *) const = 0;
};
#endif

