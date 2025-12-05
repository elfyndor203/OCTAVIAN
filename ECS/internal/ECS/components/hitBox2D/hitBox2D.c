#include "hitBox2D_internal.h"

#include "ECS/entitySet/entitySet_internal.h"
#include "ECS/components/position2D/position2D_internal.h"

size_t iOCT_hitBox2D_max = iOCT_ENTITY_DEFAULT_MAX;

iOCT_hitBox2D* iOCT_hitBox2D_get(iOCT_entitySetID entitySetID, iOCT_entityID parentID) {
    iOCT_entitySet* entitySet = iOCT_entitySet_get(entitySetID);
    if (entitySet == iOCT_GET_FAILED || parentID >= entitySet->entityCounter) {
        OCT_logError(ERR_HITBOX2D_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }
    iOCT_entity* parent = iOCT_entity_get(entitySetID, parentID);
    if (parent == iOCT_GET_FAILED) {
        printf("failCheck 2\n");
        OCT_logError(ERR_HITBOX2D_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }
    if (parent->hitBoxID == iOCT_NO_COMPONENT) {
        printf("failCheck 3\n");
        OCT_logError(ERR_HITBOX2D_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    printf("Got hitBox2D from entity #%zu from entitySet #%zu\n", parentID, entitySetID);
    return &entitySet->hitBox2DPool[parent->hitBoxID];
}

iOCT_hitBox2D* iOCT_hitBox2D_getPool(iOCT_entitySetID entitySetID) {
    iOCT_entitySet* entitySet = iOCT_entitySet_get(entitySetID);
    if (entitySet == iOCT_GET_FAILED) {
        OCT_logError(ERR_HITBOX2DPOOL_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    printf("Got hitBox2D pool from entitySet #%zu\n", entitySetID);
    return entitySet->hitBox2DPool; // array decays to pointer
}
OCT_counter* iOCT_hitBox2D_getCounter(iOCT_entitySetID entitySetID) {
    iOCT_entitySet* entitySet = iOCT_entitySet_get(entitySetID);
    if (entitySet == iOCT_GET_FAILED) {
        OCT_logError(ERR_HITBOX2DCOUNTER_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    printf("Got hitBox2D counter from entitySet #%zu\n", entitySetID);
    return &entitySet->hitBox2DCounter;
}

iOCT_componentID iOCT_hitBox2D_addNew(iOCT_entitySetID entitySetID, iOCT_entityID parentID) {
    // Check if parent already has a hitBox2D component
    if (iOCT_entity_hasComponent(entitySetID, parentID, componentHitBox2D)) {
        OCT_logError(WARNING_COMPONENT_REPLACED);
    }

    // Get the counter and ensure the pool is not full
    OCT_counter* counter = iOCT_hitBox2D_getCounter(entitySetID);
    if (*counter >= iOCT_hitBox2D_max) {
        OCT_logError(ERR_HITBOX2DPOOL_FULL);
        return iOCT_HITBOX2D_FAILED;
    }

    iOCT_hitBox2D newHitBox2D = { 0 };

    // Get parent object and mark it as having this component
    iOCT_entity* parent = iOCT_entity_get(entitySetID, parentID);
    parent->componentsMask |= (1ULL << componentHitBox2D);

    // Set bookkeeping values
    iOCT_componentID hitBoxID = *counter;
    newHitBox2D.hitBoxID = hitBoxID;
    newHitBox2D.parentID = parentID;
    parent->hitBoxID = hitBoxID;

    // Add to the pool
    iOCT_hitBox2D_getPool(entitySetID)[*counter] = newHitBox2D;

    iOCT_hitBox2D_resize(entitySetID, parentID, DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y);

    // Increment the counter
    *counter += 1;

    printf("Added new hitBox2D to object #%zu in entitySet #%zu\n", parentID, entitySetID);
    return hitBoxID;
}


void iOCT_hitBox2D_resize(iOCT_entitySetID entitySetID, iOCT_entityID parentIndex, float sizeX, float sizeY) {
    printf("Resizing hitbox...\n");
	iOCT_hitBox2D_get(entitySetID, parentIndex)->size.x = sizeX;
	iOCT_hitBox2D_get(entitySetID, parentIndex)->size.y = sizeY;

	iOCT_hitBox2D_generateVertices(entitySetID, parentIndex);
}

void iOCT_hitBox2D_generateVertices(entitySetID, parentID) {
    iOCT_hitBox2D* hitBox = iOCT_hitBox2D_get(entitySetID, parentID);
    OCT_vector2D hitBoxWidth = { hitBox->size.x, 0 };
    OCT_vector2D hitBoxHeight = { 0, hitBox->size.y };
    OCT_vector2D totalOffset = OCT_vector2D_Vector2D(OCT_OP_ADD, hitBox->localOrigin, iOCT_position2D_get(entitySetID, parentID)->globalPosition2D);

    OCT_vertex2D bottomLeft = OCT_vector2D_Vector2DMulti(OCT_OP_ADD, 3, totalOffset, hitBox->localOrigin, OCT_vector2D_Scalar(OCT_OP_DIVIDE, hitBox->size, -2.0f));
    OCT_vertex2D bottomRight = OCT_vector2D_Vector2D(OCT_OP_ADD, bottomLeft, hitBoxWidth);
    OCT_vertex2D topRight = OCT_vector2D_Vector2D(OCT_OP_ADD, bottomRight, hitBoxHeight);
    OCT_vertex2D topLeft = OCT_vector2D_Vector2D(OCT_OP_ADD, topRight, OCT_vector2D_Scalar(OCT_OP_MULTIPLY, hitBoxHeight, -1));
    printf("Generated vertices (%f, %f), (%f, %f), (%f, %f), (%f, %f)\n", bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, topRight.x, topRight.y, topLeft.x, topLeft.y);

    iOCT_hitBox2DVertices newVertices = {
        hitBox->localOrigin,
        bottomLeft,
        bottomRight,
        topRight,
        topLeft
    };

    hitBox->boxVertices = newVertices;
}