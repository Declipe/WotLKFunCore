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

#ifndef _BIH_WRAP
#define _BIH_WRAP

#include "G3D/Table.h"
#include "G3D/Array.h"
#include "G3D/Set.h"
#include "BoundingIntervalHierarchy.h"


template<class T, class BoundsFunc = BoundsTrait<T> >
class BIHWrap
{
    template<class RayCallback>
    struct MDLCallback
    {
        const T* const* objects;
        RayCallback& _callback;

        MDLCallback(RayCallback& callback, const T* const* objects_array ) : objects(objects_array), _callback(callback) {}

        bool operator() (const Ray& ray, uint32 Idx, float& MaxDist, bool /*stopAtFirst*/)
        {
            if (const T* obj = objects[Idx])
                return _callback(ray, *obj, MaxDist/*, stopAtFirst*/);
            return false;
        }

        void operator() (const Vector3& p, uint32 Idx)
        {
            if (const T* obj = objects[Idx])
                _callback(p, *obj);
        }
    };

    typedef G3D::Array<const T*> ObjArray;

    BIH m_tree;
    ObjArray m_objects;
    G3D::Table<const T*, uint32> m_obj2Idx;
    G3D::Set<const T*> m_objects_to_push;
    int unbalanced_times;

public:
    BIHWrap() : unbalanced_times(0) {}

    void insert(const T& obj)
    {
        ++unbalanced_times;
        m_objects_to_push.insert(&obj);
    }

    void remove(const T& obj)
    {
        ++unbalanced_times;
        uint32 Idx = 0;
        const T * temp;
        if (m_obj2Idx.getRemove(&obj, temp, Idx))
            m_objects[Idx] = NULL;
        else
            m_objects_to_push.remove(&obj);
    }

    void balance()
    {
        if (unbalanced_times == 0)
            return;

        unbalanced_times = 0;
        m_objects.fastClear();
        m_obj2Idx.getKeys(m_objects);
        m_objects_to_push.getMembers(m_objects);

        m_tree.build(m_objects, BoundsFunc::getBounds2);
    }

    template<typename RayCallback>
    void intersectRay(const Ray& ray, RayCallback& intersectCallback, float& maxDist) const
    {
        MDLCallback<RayCallback> temp_cb(intersectCallback, m_objects.getCArray());
        m_tree.intersectRay(ray, temp_cb, maxDist, true);
    }

    template<typename IsectCallback>
    void intersectPoint(const Vector3& point, IsectCallback& intersectCallback) const
    {
        MDLCallback<IsectCallback> callback(intersectCallback, m_objects.getCArray());
        m_tree.intersectPoint(point, callback);
    }
};

#endif // _BIH_WRAP
