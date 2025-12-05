#include "ECS/components/transform2D/transform2D_internal.h"

void OCT_transform2D_addNew(OCT_entityHandle parentHandle) {
    iOCT_entitySetID entitySetID = parentHandle.entitySetID;
    iOCT_entityID parentID = parentHandle.entityID;
    transform2D_addNew(entitySetID, parentID);
}
