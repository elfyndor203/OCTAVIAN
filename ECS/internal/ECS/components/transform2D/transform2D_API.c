#include "ECS/components/transform2D/transform2D_internal.h"

OCT_componentID OCT_transform2D_addNew(OCT_sceneID sceneID, OCT_gameObjectID parentID) {
    return (OCT_componentID)transform2D_addNew((iOCT_sceneID)sceneID, (iOCT_gameObjectID)parentID);
}