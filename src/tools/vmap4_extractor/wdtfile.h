/*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2005-2016 MaNGOS.
*
* This file is free software; as a special exception the author gives
* unlimited permission to copy and/or distribute it, with or without
* modifications, as long as this notice is preserved.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef WDTFILE_H
#define WDTFILE_H

#include "mpq_libmpq04.h"
#include "wmo.h"
#include <string>
#include "stdlib.h"

class ADTFile;

class WDTFile
{
public:
    WDTFile(char* file_name, char* file_name1);
    ~WDTFile(void);
    bool init(char *map_id, unsigned int mapID);

    string* gWmoInstansName;
    int gnWMO, nMaps;

    ADTFile* GetMap(int x, int z);

private:
    MPQFile WDT;
    bool maps[64][64];
    string filename;
};

#endif
