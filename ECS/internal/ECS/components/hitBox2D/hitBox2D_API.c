#include "hitBox2D_internal.h"

void OCT_hitBox2D_addNew(OCT_entityHandle parentHandle) {
    iOCT_entitySetID entitySetID = parentHandle.entitySetID;
    iOCT_entityID parentID = parentHandle.entityID;
    iOCT_hitBox2D_addNew(entitySetID, parentID);
}

void OCT_hitBox2D_resize(OCT_entityHandle parentHandle, float sizeX, float sizeY) {
    iOCT_entitySetID entitySetID = parentHandle.entitySetID;
    iOCT_entityID parentID = parentHandle.entityID;
    iOCT_hitBox2D_resize(entitySetID, parentID, sizeX, sizeY);
}

