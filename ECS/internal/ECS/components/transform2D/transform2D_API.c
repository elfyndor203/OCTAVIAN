#include "ECS/components/transform2D/transform2D_internal.h"

void OCT_transform2D_addNew(OCT_entityHandle parentHandle) {
    iOCT_entityContextID entitySetID = parentHandle.entitySetID;
    iOCT_entityID parentID = parentHandle.entityID;
    iOCT_transform2D_new(entitySetID, parentID);
}

void OCT_transform2D_rotate(OCT_entityHandle parentHandle, float degrees) {
    iOCT_transform2D_rotate(parentHandle.entitySetID, parentHandle.entityID, degrees);
    if (iOCT_entity_hasComponent(parentHandle.entitySetID, parentHandle.entityID, OCT_typeComponentHitBox2D)) {
        _OCT_sendMessage(_OCT_Renderer, parentHandle, _OCT_hitBox2D_update, OCT_GENERIC_NONE, OCT_GENERIC_NONE);
    }
}
