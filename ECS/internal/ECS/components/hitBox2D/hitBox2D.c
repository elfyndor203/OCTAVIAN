#include "hitBox2D_internal.h"

#include "ECS/scene/scene_internal.h"
#include "ECS/components/position2D/position2D_internal.h"

size_t iOCT_MAX_HITBOX2D = iOCT_DEFAULT_MAX_GAMEOBJECTS;

iOCT_hitBox2D* iOCT_hitBox2D_get(iOCT_sceneID sceneID, iOCT_gameObjectID parentID) {
    iOCT_scene* scene = iOCT_scene_get(sceneID);
    if (scene == iOCT_GET_FAILED || parentID >= scene->gameObjectCounter) {
        OCT_logError(ERR_HITBOX2D_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }
    iOCT_gameObject* parentObject = iOCT_gameObject_get(sceneID, parentID);
    if (parentObject == iOCT_GET_FAILED) {
        printf("failCheck 2\n");
        OCT_logError(ERR_HITBOX2D_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }
    if (parentObject->hitBoxID == iOCT_NO_COMPONENT) {
        printf("failCheck 3\n");
        OCT_logError(ERR_HITBOX2D_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    printf("Got hitBox2D from gameObject #%zu from scene #%zu\n", parentID, sceneID);
    return &scene->hitBox2DPool[parentObject->hitBoxID];
}
iOCT_hitBox2D* iOCT_hitBox2D_getPool(iOCT_sceneID sceneID) {
    iOCT_scene* scene = iOCT_scene_get(sceneID);
    if (scene == iOCT_GET_FAILED) {
        OCT_logError(ERR_HITBOX2DPOOL_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    printf("Got hitBox2D pool from scene #%zu\n", sceneID);
    return scene->hitBox2DPool; // array decays to pointer
}
iOCT_counter* iOCT_hitBox2D_getCounter(iOCT_sceneID sceneID) {
    iOCT_scene* scene = iOCT_scene_get(sceneID);
    if (scene == iOCT_GET_FAILED) {
        OCT_logError(ERR_HITBOX2DCOUNTER_DOES_NOT_EXIST);
        return iOCT_GET_FAILED;
    }

    printf("Got hitBox2D counter from scene #%zu\n", sceneID);
    return &scene->hitBox2DCounter;
}

iOCT_componentID iOCT_hitBox2D_addNew(iOCT_sceneID sceneID, iOCT_gameObjectID parentID) {
    // Check if parent already has a hitBox2D component
    if (iOCT_gameObject_hasComponent(sceneID, parentID, componentHitBox2D)) {
        OCT_logError(WARNING_COMPONENT_REPLACED);
    }

    // Get the counter and ensure the pool is not full
    iOCT_counter* counter = iOCT_hitBox2D_getCounter(sceneID);
    if (*counter >= iOCT_MAX_HITBOX2D) {
        OCT_logError(ERR_HITBOX2DPOOL_FULL);
        return iOCT_HITBOX2D_FAILED;
    }

    iOCT_hitBox2D newHitBox2D = { 0 };

    // Get parent object and mark it as having this component
    iOCT_gameObject* parentObject = iOCT_gameObject_get(sceneID, parentID);
    parentObject->componentsMask |= (1ULL << componentHitBox2D);

    // Set bookkeeping values
    OCT_componentID hitBoxID = *counter;
    newHitBox2D.hitBoxID = hitBoxID;
    newHitBox2D.parentID = parentID;
    parentObject->hitBoxID = hitBoxID;

    // Add to the pool
    iOCT_hitBox2D_getPool(sceneID)[*counter] = newHitBox2D;

    iOCT_hitBox2D_resize(sceneID, parentID, DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y);

    // Increment the counter
    *counter += 1;

    printf("Added new hitBox2D to object #%zu in scene #%zu\n", parentID, sceneID);
    return hitBoxID;
}


void iOCT_hitBox2D_resize(iOCT_sceneID sceneID, iOCT_gameObjectID parentIndex, float sizeX, float sizeY) {
    printf("Resizing hitbox...\n");
	iOCT_hitBox2D_get(sceneID, parentIndex)->size.x = sizeX;
	iOCT_hitBox2D_get(sceneID, parentIndex)->size.y = sizeY;

	iOCT_hitBox2D_generateVertices(sceneID, parentIndex);
}

void iOCT_hitBox2D_generateVertices(sceneID, parentID) {
    iOCT_hitBox2D* hitBox = iOCT_hitBox2D_get(sceneID, parentID);
    OCT_vector2D hitBoxWidth = { hitBox->size.x, 0 };
    OCT_vector2D hitBoxHeight = { 0, hitBox->size.y };
    OCT_vector2D totalOffset = OCT_vector2D_Vector2D(OCT_OP_ADD, hitBox->localOrigin, iOCT_position2D_get(sceneID, parentID)->globalPosition2D);

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