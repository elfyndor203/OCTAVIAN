#include "ECS/components/position2D/position2D_internal.h"

void OCT_position2D_addNew(OCT_entityHandle parentHandle) {
    iOCT_entitySetID entitySetID = parentHandle.entitySetID;
    iOCT_entityID parentID = parentHandle.entityID;
    iOCT_position2D_addNew(entitySetID, parentID);
}

void OCT_position2D_move(OCT_entityHandle parentHandle, float x, float y) {
    OCT_vector2D distance = { x, y };
    iOCT_position2D_move(parentHandle.entitySetID, parentHandle.entityID, distance);
    if (iOCT_entity_hasComponent(parentHandle.entitySetID, parentHandle.entityID, componentHitBox2D)) {
        _OCT_sendMessage(_OCT_Renderer, parentHandle, _OCT_hitBox2D_update, GENERIC_NONE);
    }
}
