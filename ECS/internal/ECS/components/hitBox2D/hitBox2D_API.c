#include "hitBox2D_internal.h"

OCT_componentID OCT_hitBox2D_addNew(OCT_gameObjectHandle parentObjectHandle) {
    iOCT_sceneID sceneID = parentObjectHandle.sceneID;
    iOCT_gameObjectID parentID = parentObjectHandle.gameObjectID;
    return iOCT_hitBox2D_addNew(sceneID, parentID);
}

void OCT_hitBox2D_resize(OCT_gameObjectHandle parentObjectHandle, float sizeX, float sizeY) {
    iOCT_sceneID sceneID = parentObjectHandle.sceneID;
    iOCT_gameObjectID parentID = parentObjectHandle.gameObjectID;
    iOCT_hitBox2D_resize(sceneID, parentID, sizeX, sizeY);
}

