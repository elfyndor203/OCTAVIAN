#include "ECS/components/transform2D/transform2D_internal.h"

OCT_componentID OCT_transform2D_addNew(OCT_gameObjectHandle parentObjectHandle) {
    iOCT_sceneID sceneID = parentObjectHandle.sceneID;
    iOCT_gameObjectID parentID = parentObjectHandle.gameObjectID;
    return (OCT_componentID)transform2D_addNew(sceneID, parentID);
}
