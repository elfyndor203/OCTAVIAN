#include "ECS/components/position2D/position2D_internal.h"

OCT_componentID OCT_position2D_addNew(OCT_gameObjectHandle parentObjectHandle) {
    iOCT_sceneID sceneID = parentObjectHandle.sceneID;
    iOCT_gameObjectID parentID = parentObjectHandle.gameObjectID;
    return iOCT_position2D_addNew(sceneID, parentID);
}

