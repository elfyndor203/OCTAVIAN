#include "hitBox2D_internal.h"

void OCT_hitBox2D_addNew(OCT_entityHandle parentHandle, size_t layer) { // NOTE_LINKS_THE_TWO_UNSURE_IF_GOOD
    iOCT_entitySetID entitySetID = parentHandle.entitySetID;
    iOCT_entityID parentID = parentHandle.entityID;
    iOCT_hitBox2D_addNew(entitySetID, parentID);
    _OCT_sendMessage(_OCT_Renderer, parentHandle, _OCT_hitBox2D_add, (float)layer, OCT_GENERIC_NONE);   // NOTE_MOVE_MAYBE
}

void OCT_hitBox2D_resize(OCT_entityHandle parentHandle, float sizeX, float sizeY) {
    if (iOCT_entity_hasComponent(parentHandle.entitySetID, parentHandle.entityID, OCT_componentHitBox2D) == false) {
        OCT_logError(ERR_HITBOX2D_DOES_NOT_EXIST);
        return;
    }
    iOCT_entitySetID entitySetID = parentHandle.entitySetID;
    iOCT_entityID parentID = parentHandle.entityID;
    iOCT_hitBox2D_resize(entitySetID, parentID, sizeX, sizeY);
    _OCT_sendMessage(_OCT_Renderer, parentHandle, _OCT_hitBox2D_update, OCT_GENERIC_NONE, OCT_GENERIC_NONE);
}

