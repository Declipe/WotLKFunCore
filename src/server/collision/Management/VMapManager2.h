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

#ifndef _VMAPMANAGER2_H
#define _VMAPMANAGER2_H

#include "IVMapManager.h"
#include "Dynamic/UnorderedMap.h"
#include "Define.h"
#include <ace/Thread_Mutex.h>

//===========================================================

#define MAP_FILENAME_EXTENSION2 ".vmtree"

#define FILENAMEBUFFER_SIZE 500

/**
This is the main Class to manage loading and unloading of maps, line of sight, height calculation and so on.
For each map or map tile to load it reads a directory file that contains the ModelContainer files used by this map or map tile.
Each global map or instance has its own dynamic BSP-Tree.
The loaded ModelContainers are included in one of these BSP-Trees.
Additionally a table to match map ids and map names is used.
*/

//===========================================================

namespace G3D
{
    class Vector3;
}

namespace VMAP
{
    class StaticMapTree;
    class WorldModel;

    class ManagedModel
    {
        public:
            ManagedModel() : iModel(0), iRefCount(0) {}
            void setModel(WorldModel* model) { iModel = model; }
            WorldModel* getModel() { return iModel; }
            void incRefCount() { ++iRefCount; }
            int decRefCount() { return --iRefCount; }
        protected:
            WorldModel* iModel;
            int iRefCount;
    };

    typedef UNORDERED_MAP<uint32, StaticMapTree*> InstanceTreeMap;
    typedef UNORDERED_MAP<std::string, ManagedModel> ModelFileMap;

    class VMapManager2 : public IVMapManager
    {
        protected:
            // Tree to check collision
            ModelFileMap iLoadedModelFiles;
            InstanceTreeMap iInstanceMapTrees;
            // Mutex for iLoadedModelFiles
            ACE_Thread_Mutex LoadedModelFilesLock;

            bool _loadMap(uint32 mapId, const std::string& basePath, uint32 tileX, uint32 tileY);
            /* void _unloadMap(uint32 pMapId, uint32 x, uint32 y); */

        public:
            // public for debug
            G3D::Vector3 convertPositionToInternalRep(float x, float y, float z) const;
            static std::string getMapFileName(unsigned int mapId);

            VMapManager2();
            ~VMapManager2(void);

            int loadMap(const char* pBasePath, unsigned int mapId, int x, int y);

            void unloadMap(unsigned int mapId, int x, int y);
            void unloadMap(unsigned int mapId);

            bool isInLineOfSight(unsigned int mapId, float x1, float y1, float z1, float x2, float y2, float z2) ;
            /**
            fill the hit pos and return true, if an object was hit
            */
            bool getObjectHitPos(unsigned int mapId, float x1, float y1, float z1, float x2, float y2, float z2, float& rx, float& ry, float& rz, float modifyDist);
            float getHeight(unsigned int mapId, float x, float y, float z, float maxSearchDist);

            bool processCommand(char* /*command*/) { return false; } // for debug and extensions

            bool getAreaInfo(unsigned int pMapId, float x, float y, float& z, uint32& flags, int32& adtId, int32& rootId, int32& groupId) const;
            bool GetLiquidLevel(uint32 pMapId, float x, float y, float z, uint8 reqLiquidType, float& level, float& floor, uint32& type) const;

            WorldModel* acquireModelInstance(const std::string& basepath, const std::string& filename);
            void releaseModelInstance(const std::string& filename);

            // what's the use of this? o.O
            virtual std::string getDirFileName(unsigned int mapId, int /*x*/, int /*y*/) const
            {
                return getMapFileName(mapId);
            }
            virtual bool existsMap(const char* basePath, unsigned int mapId, int x, int y);
    };
}

#endif
