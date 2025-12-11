#include "transform2D_internal.h"

#include "ECS/entity/entity_internal.h"
#include "ECS/entitySet/entitySet_internal.h"

size_t iOCT_MAX_TRANSFORM2D = iOCT_ENTITY_DEFAULT_MAX;

OCT_vector2D defaultScale = { DEFAULT_SCALE_X, DEFAULT_SCALE_Y };

iOCT_transform2D* iOCT_transform2D_get(iOCT_entitySetID entitySetID, iOCT_entityID parentID) {
    iOCT_entitySet* entitySet = iOCT_entitySet_get(entitySetID);
    if (entitySet == iOCT_GET_FAILED || parentID >= entitySet->entityCounter) {
        OCT_logError(ERR_TRANSFORM2D_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    iOCT_entity* parent = iOCT_entity_get(entitySetID, parentID);
    if (parent == iOCT_GET_FAILED) {
        OCT_logError(ERR_TRANSFORM2D_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    if (parent->transformID == iOCT_NO_COMPONENT) {
        OCT_logError(ERR_TRANSFORM2D_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    //printf("Got transform2D from entity #%zu from entitySet #%zu\n", parentID, entitySetID);
    return &entitySet->transform2DPool[parent->transformID];
}
iOCT_transform2D* iOCT_transform2D_getPool(iOCT_entitySetID entitySetID) {
    iOCT_entitySet* entitySet = iOCT_entitySet_get(entitySetID);
    if (entitySet == iOCT_GET_FAILED) {
        OCT_logError(ERR_TRANSFORM2DPOOL_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    //printf("Got transform2D pool from entitySet #%zu\n", entitySetID);
    return entitySet->transform2DPool;
}
OCT_counter* iOCT_transform2D_getCounter(iOCT_entitySetID entitySetID) {
    iOCT_entitySet* entitySet = iOCT_entitySet_get(entitySetID);
    if (entitySet == iOCT_GET_FAILED) {
        OCT_logError(ERR_TRANSFORM2DCOUNTER_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

   // printf("Got transform2D counter from entitySet #%zu\n", entitySetID);
    return &entitySet->transform2DCounter;
}



iOCT_componentID transform2D_addNew(iOCT_entitySetID entitySetID, iOCT_entityID parentID) {
    // Check if parent already has a transform component
    if (iOCT_entity_hasComponent(entitySetID, parentID, OCT_componentTransform2D)) {
        OCT_logError(WARNING_COMPONENT_REPLACED);
    }

    // Get counter and ensure pool is not full
    OCT_counter* counter = iOCT_transform2D_getCounter(entitySetID);
    if (*counter >= iOCT_MAX_TRANSFORM2D) {
        OCT_logError(ERR_TRANSFORM2DPOOL_FULL);
        return iOCT_TRANSFORM2D_FAILED;
    }

    iOCT_transform2D newTransform = { 0 };

    // Get parent object and mark it as having this component
    iOCT_entity* parent = iOCT_entity_get(entitySetID, parentID);
    parent->componentsMask |= (1ULL << OCT_componentTransform2D);

    // Set IDs
    iOCT_componentID transformID = *counter;
    newTransform.transformID = transformID;
    newTransform.parentID = parentID;
    parent->transformID = transformID;

    // Set default transform values
    newTransform.rotation = DEFAULT_ROTATION;
    newTransform.scale = defaultScale;

    // Add to the pool
    iOCT_transform2D_getPool(entitySetID)[*counter] = newTransform;

    // Increment counter
    *counter += 1;

    printf("Added new transform2D to object #%zu in entitySet #%zu\n", parentID, entitySetID);
    return transformID;
}

void iOCT_transform2D_rotate(iOCT_entitySetID entitySetID, iOCT_entityID parentID, float degrees) {
    iOCT_transform2D_get(entitySetID, parentID)->rotation -= OCT_deg2rad(degrees);  //NOTE_FOR_CCW_UNSURE_WHY
}

