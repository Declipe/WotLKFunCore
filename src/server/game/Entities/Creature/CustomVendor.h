/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
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

#ifndef CUSTOMVENDOR_H
#define CUSTOMVENDOR_H
extern WorldDatabaseWorkerPool WorldDatabase;

class VendorEntry
{
public:
	int id, vendor, group, next;
	std::string desc;
	VendorEntry(int, int, int, int, std::string);
};

typedef std::list<VendorEntry *> VendorEntryList;

class CustomVendor
{
public:
	VendorEntryList vendorEntryList;
	CustomVendor(void);
	~CustomVendor(void);
	int LoadVendors(void);
	VendorEntryList* GetItemsForEntry(int, int);
	VendorEntryList* GetBaseItemsForEntry(int);
	int GetGroup(int);
	int GetNext(int, int);
	VendorEntry* GetParent(int);
};

extern CustomVendor CustomVendorMgr;

#endif