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

#ifndef TRINITY_TYPELIST_H
#define TRINITY_TYPELIST_H

/*
  @struct TypeList
  TypeList is the most simple but yet the most powerfull class of all.  It holds
  at compile time the different type of objects in a linked list.
 */

class TypeNull;

template<typename HEAD, typename TAIL>
struct TypeList
{
    typedef HEAD Head;
    typedef TAIL Tail;
};

// enough for now.. can be expand at any point in time as needed
#define TYPELIST_1(T1)                  TypeList<T1, TypeNull>
#define TYPELIST_2(T1, T2)              TypeList<T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3)          TypeList<T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4)      TypeList<T1, TYPELIST_3(T2, T3, T4) >
#define TYPELIST_5(T1, T2, T3, T4, T5)  TypeList<T1, TYPELIST_4(T2, T3, T4, T5) >
#endif

