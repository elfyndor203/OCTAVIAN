#include "transform2D_internal.h"

#include "ECS/gameObject/gameObject_internal.h"
#include "ECS/scene/scene_internal.h"

OCT_vector2D defaultScale = { DEFAULT_SCALE_X, DEFAULT_SCALE_Y };

iOCT_transform2D* iOCT_transform2D_get(iOCT_sceneID sceneID, iOCT_componentID transformID) {
    iOCT_scene* scene = iOCT_scene_get(sceneID);
    if (scene == iOCT_GET_FAILED || transformID >= scene->transform2DCounter) {
        OCT_logError(ERR_TRANSFORM2D_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    printf("Got transform2D #%zu from scene #%zu\n", transformID, sceneID);
    return &scene->transform2DPool[transformID];
}
iOCT_transform2D* iOCT_transform2D_getPool(iOCT_sceneID sceneID) {
    iOCT_scene* scene = iOCT_scene_get(sceneID);
    if (scene == iOCT_GET_FAILED) {
        OCT_logError(ERR_TRANSFORM2DPOOL_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    printf("Got transform2D pool from scene #%zu\n", sceneID);
    return scene->transform2DPool;
}
iOCT_counter* iOCT_transform2D_getCounter(iOCT_sceneID sceneID) {
    iOCT_scene* scene = iOCT_scene_get(sceneID);
    if (scene == iOCT_GET_FAILED) {
        OCT_logError(ERR_TRANSFORM2DCOUNTER_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    printf("Got transform2D counter from scene #%zu\n", sceneID);
    return &scene->transform2DCounter;
}



iOCT_componentID transform2D_addNew(iOCT_sceneID sceneID, iOCT_gameObjectID parentID) {
    // Check if parent already has a transform component
    if (iOCT_gameObject_hasComponent(sceneID, parentID, componentTransform2D)) {
        OCT_logError(WARNING_COMPONENT_REPLACED);
    }

    // Get counter and ensure pool is not full
    iOCT_counter* counter = iOCT_transform2D_getCounter(sceneID);
    if (*counter >= iOCT_MAX_TRANSFORM2D) {
        OCT_logError(ERR_TRANSFORM2DPOOL_FULL);
        return iOCT_TRANSFORM2D_FAILED;
    }

    iOCT_transform2D newTransform = { 0 };

    // Get parent object and mark it as having this component
    iOCT_gameObject* parentObject = iOCT_gameObject_get(sceneID, parentID);
    parentObject->componentsMask |= (1ULL << componentTransform2D);

    // Set IDs
    OCT_componentID transformID = *counter;
    newTransform.transformID = transformID;
    newTransform.parentID = parentID;
    parentObject->transformID = transformID;

    // Set default transform values
    newTransform.rotation = DEFAULT_ROTATION;
    newTransform.scale = defaultScale;

    // Add to the pool
    iOCT_transform2D_getPool(sceneID)[*counter] = newTransform;

    // Increment counter
    *counter += 1;

    printf("Added new transform2D to object #%zu in scene #%zu\n", parentID, sceneID);
    return transformID;
}

