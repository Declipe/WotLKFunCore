/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
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

#ifndef _TRINITY_AUTO_PTR_H
#define _TRINITY_AUTO_PTR_H

#include <ace/Bound_Ptr.h>

namespace Trinity
{
    template <class Pointer, class Lock>
    class AutoPtr : public ACE_Strong_Bound_Ptr<Pointer, Lock>
    {
        public:
            AutoPtr() : ACE_Strong_Bound_Ptr<Pointer, Lock>() {}
 
            AutoPtr(Pointer* x)
            {
                ACE_Strong_Bound_Ptr<Pointer, Lock>::reset(x);
            }

            operator bool() const
            {
                return ACE_Strong_Bound_Ptr<Pointer, Lock>::get() != NULL;
            }

            bool operator !() const
            {
                return ACE_Strong_Bound_Ptr<Pointer, Lock>::get() == NULL;
            }

            bool operator !=(Pointer* x) const
            {
                return ACE_Strong_Bound_Ptr<Pointer, Lock>::get() != x;
            }
    };
};

#endif