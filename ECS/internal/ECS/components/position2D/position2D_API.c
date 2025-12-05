#include "ECS/components/position2D/position2D_internal.h"

void OCT_position2D_addNew(OCT_entityHandle parentHandle) {
    iOCT_entitySetID entitySetID = parentHandle.entitySetID;
    iOCT_entityID parentID = parentHandle.entityID;
    iOCT_position2D_addNew(entitySetID, parentID);
}

