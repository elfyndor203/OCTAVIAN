#include "transform2D_internal.h"

#include "ECS/entity/entity_internal.h"
#include "ECS/entityContext/entityContext_internal.h"

size_t iOCT_MAX_TRANSFORM2D = iOCT_ENTITY_DEFAULT_MAX;

OCT_vector2D defaultScale = { DEFAULT_SCALE_X, DEFAULT_SCALE_Y };

iOCT_ID iOCT_transform2D_new(iOCT_ID entityContextID, iOCT_ID parentID) {
    iOCT_transform2D newTransform = { 0 };

    // Get parent object and mark it as having this component
    iOCT_entity_updateMask(entityContextID, parentID, OCT_typeComponentTransform2D);

    // Set IDs
    iOCT_ID transformID = *counter;
    newTransform.transformID = transformID;
    newTransform.parentID = parentID;
    parent->transformID = transformID;

    // Set default transform values
    newTransform.rotation = DEFAULT_ROTATION;
    newTransform.scale = defaultScale;

    // Add to the pool
    iOCT_transform2D_getPool(entityContextID)[*counter] = newTransform;

    // Increment counter
    *counter += 1;

    printf("Added new transform2D to object #%zu in entitySet #%zu\n", parentID, entityContextID);
    return transformID;
}

void iOCT_transform2D_rotate(iOCT_entityContextID entitySetID, iOCT_entityID parentID, float degrees) {
    iOCT_transform2D_get(entitySetID, parentID)->rotation -= OCT_deg2rad(degrees);  //NOTE_FOR_CCW_UNSURE_WHY
}

