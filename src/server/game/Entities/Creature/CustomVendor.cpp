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

#include "CustomVendor.h"
#include "Common.h"
#include "MapManager.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "ObjectDefines.h"
#include "Opcodes.h"
#include "SharedDefines.h"
#include "ObjectMgr.h"
#include <stdio.h>
#include <string>
#include <list>

CustomVendor CustomVendorMgr;

CustomVendor::CustomVendor(void)
{
}


CustomVendor::~CustomVendor(void)
{
}

int CustomVendor::LoadVendors(void)
{
	vendorEntryList.clear();
	int i = 0;
	QueryResult result = WorldDatabase.PQuery("SELECT `id`, `vendor`, `group`, `next`, `desc` FROM npc_vendor_custom");
	//												  0	  1		  2		 3	   4   
	if (result)
	{
		do
		{
			Field *fields = result->Fetch();
			int id = fields[0].GetInt32();
			int vendor = fields[1].GetInt32();
			int group = fields[2].GetInt32();
			int next = fields[3].GetInt32();
			std::string desc = fields[4].GetString();
			vendorEntryList.push_back(new VendorEntry(id, vendor, group, next, desc));
			i++;
		}
    	while (result->NextRow());
	}

	return i;
}

VendorEntryList* CustomVendor::GetItemsForEntry(int entry, int id)
{
	VendorEntryList *result = new VendorEntryList();
	VendorEntryList::iterator i;
	int group = GetGroup(id);
	for (i = vendorEntryList.begin(); i != vendorEntryList.end(); ++i)
	{
		VendorEntry *vendorEntry = *i;
		if(vendorEntry->group == group && vendorEntry->vendor == entry)
			result->push_back(vendorEntry);
	}
	return result;
}

VendorEntryList* CustomVendor::GetBaseItemsForEntry(int entry)
{
	VendorEntryList *result = new VendorEntryList();
	VendorEntryList::iterator i;
	for (i = vendorEntryList.begin(); i != vendorEntryList.end(); ++i)
	{
		VendorEntry *vendorEntry = *i;
		if(vendorEntry->group == 0 && vendorEntry->vendor == entry)
			result->push_back(vendorEntry);
	}
	return result;
}

int CustomVendor::GetGroup(int id)
{
	VendorEntryList::iterator i;
	for (i = vendorEntryList.begin(); i != vendorEntryList.end(); ++i)
	{
		VendorEntry *vendorEntry = *i;
		if(vendorEntry->id == id)
			return vendorEntry->group;
	}
	return -1;
}

int CustomVendor::GetNext(int entry, int id)
{
	VendorEntryList::iterator i;
	for (i = vendorEntryList.begin(); i != vendorEntryList.end(); ++i)
	{
		VendorEntry *vendorEntry = *i;
		if(vendorEntry->id == id && vendorEntry->vendor == entry)
			return vendorEntry->next;
	}
	return -1;
}

VendorEntry* CustomVendor::GetParent(int id)
{
	VendorEntryList::iterator i;
	for (i = vendorEntryList.begin(); i != vendorEntryList.end(); ++i)
	{
		VendorEntry *vendorEntry = *i;
		if(vendorEntry->next == id)
			return vendorEntry;
	}

	return NULL;
}

VendorEntry::VendorEntry(int id, int vendor, int group, int next, std::string desc)
{
	this->id = id;
	this->vendor = vendor;
	this->group = group;
	this->next = next;
	this->desc = desc;
}