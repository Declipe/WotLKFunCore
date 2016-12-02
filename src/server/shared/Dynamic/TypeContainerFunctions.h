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

#ifndef TYPECONTAINER_FUNCTIONS_H
#define TYPECONTAINER_FUNCTIONS_H

/*
 * Here you'll find a list of helper functions to make
 * the TypeContainer usefull.  Without it, its hard
 * to access or mutate the container.
 */

#include "Define.h"
#include "Dynamic/TypeList.h"
#include <map>

namespace Trinity
{
    /* ContainerMapList Helpers */
    // count functions
    template<class SPECIFIC_TYPE> size_t Count(const ContainerMapList<SPECIFIC_TYPE> &elements, SPECIFIC_TYPE* /*fake*/)
    {
        return elements._element.getSize();
    };

    template<class SPECIFIC_TYPE> size_t Count(const ContainerMapList<TypeNull> &/*elements*/, SPECIFIC_TYPE* /*fake*/)
    {
        return 0;
    }

    template<class SPECIFIC_TYPE, class T> size_t Count(const ContainerMapList<T> &/*elements*/, SPECIFIC_TYPE* /*fake*/)
    {
        return 0;
    }

    template<class SPECIFIC_TYPE, class T> size_t Count(const ContainerMapList<TypeList<SPECIFIC_TYPE, T> >&elements, SPECIFIC_TYPE* fake)
    {
        return Count(elements._elements, fake);
    }

    template<class SPECIFIC_TYPE, class H, class T> size_t Count(const ContainerMapList<TypeList<H, T> >&elements, SPECIFIC_TYPE* fake)
    {
        return Count(elements._TailElements, fake);
    }

    // non-const insert functions
    template<class SPECIFIC_TYPE> SPECIFIC_TYPE* Insert(ContainerMapList<SPECIFIC_TYPE> &elements, SPECIFIC_TYPE *obj)
    {
        //elements._element[hdl] = obj;
        obj->AddToGrid(elements._element);
        return obj;
    };

    template<class SPECIFIC_TYPE> SPECIFIC_TYPE* Insert(ContainerMapList<TypeNull> &/*elements*/, SPECIFIC_TYPE * /*obj*/)
    {
        return NULL;
    }

    // this is a missed
    template<class SPECIFIC_TYPE, class T> SPECIFIC_TYPE* Insert(ContainerMapList<T> &/*elements*/, SPECIFIC_TYPE * /*obj*/)
    {
        return NULL;                                        // a missed
    }

    // Recursion
    template<class SPECIFIC_TYPE, class H, class T> SPECIFIC_TYPE* Insert(ContainerMapList<TypeList<H, T> >&elements, SPECIFIC_TYPE *obj)
    {
        SPECIFIC_TYPE* t= Insert(elements._elements, obj);
        return (t != NULL ? t : Insert(elements._TailElements, obj));
    }

    //// non-const remove method
    //template<class SPECIFIC_TYPE> SPECIFIC_TYPE* Remove(ContainerMapList<SPECIFIC_TYPE> & /*elements*/, SPECIFIC_TYPE *obj)
    //{
    //    obj->GetGridRef().unlink();
    //    return obj;
    //}

    //template<class SPECIFIC_TYPE> SPECIFIC_TYPE* Remove(ContainerMapList<TypeNull> &/*elements*/, SPECIFIC_TYPE * /*obj*/)
    //{
    //    return NULL;
    //}

    //// this is a missed
    //template<class SPECIFIC_TYPE, class T> SPECIFIC_TYPE* Remove(ContainerMapList<T> &/*elements*/, SPECIFIC_TYPE * /*obj*/)
    //{
    //    return NULL;                                        // a missed
    //}

    //template<class SPECIFIC_TYPE, class T, class H> SPECIFIC_TYPE* Remove(ContainerMapList<TypeList<H, T> > &elements, SPECIFIC_TYPE *obj)
    //{
    //    // The head element is bad
    //    SPECIFIC_TYPE* t = Remove(elements._elements, obj);
    //    return ( t != NULL ? t : Remove(elements._TailElements, obj) );
    //}
}
#endif

