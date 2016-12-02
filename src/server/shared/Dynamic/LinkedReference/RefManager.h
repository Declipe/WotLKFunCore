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

#ifndef _REFMANAGER_H
#define _REFMANAGER_H
//=====================================================

#include "Dynamic/LinkedList.h"
#include "Dynamic/LinkedReference/Reference.h"

template <class TO, class FROM> class RefManager : public LinkedListHead
{
    public:
        typedef LinkedListHead::Iterator< Reference<TO, FROM> > iterator;
        RefManager() { }
        virtual ~RefManager() { clearReferences(); }

        Reference<TO, FROM>* getFirst() { return ((Reference<TO, FROM>*) LinkedListHead::getFirst()); }
        Reference<TO, FROM> const* getFirst() const { return ((Reference<TO, FROM> const*) LinkedListHead::getFirst()); }
        Reference<TO, FROM>* getLast() { return ((Reference<TO, FROM>*) LinkedListHead::getLast()); }
        Reference<TO, FROM> const* getLast() const { return ((Reference<TO, FROM> const*) LinkedListHead::getLast()); }

        iterator begin() { return iterator(getFirst()); }
        iterator end() { return iterator(NULL); }
        iterator rbegin() { return iterator(getLast()); }
        iterator rend() { return iterator(NULL); }

        void clearReferences()
        {
            LinkedListElement* ref;
            while ((ref = getFirst()) != NULL)
            {
                ((Reference<TO, FROM>*) ref)->invalidate();
                ref->delink();                              // the delink might be already done by invalidate(), but doing it here again does not hurt and insures an empty list
            }
        }
};

//=====================================================
#endif

