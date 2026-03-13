#include "transform2D_internal.h"
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "OCT_Errors.h"
#include "OCT_EngineStructure.h"
#include "OCT_Math.h"
#include "units/constants.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/entityContext/entityContext_internal.h"
#include "ECS/entityContext/registry_internal.h"

static int currentMaxDepth = -1;
static OCT_index depthEnds[iOCT_TRANSFORM_MAXDEPTH] = {0}; // marks the end index of each depth group

static OCT_mat3 iOCT_transform2D_generateMatrix(iOCT_transform2D transform);
static void iOCT_transform2D_sort(OCT_ID contextID, iOCT_transform2D newTransform);
static iOCT_transform2D iOCT_transform2D_getParentU(OCT_ID contextID, OCT_ID entityID);

iOCT_transform2D* iOCT_transform2D_get(OCT_ID entityContextID, OCT_ID entityID) {
    return (iOCT_transform2D*)iOCT_getByID(entityContextID, entityID, OCT_typeComponentTransform2D);
}

/// <summary>
/// Attaches a new transform2D component to the chosen entity. Returns false if anything failed.
/// </summary>
/// <param name="parentHandle"></param>
/// <returns></returns>
bool OCT_transform2D_add(OCT_entityHandle parentHandle) {
    if (iOCT_transform2D_add(parentHandle.entityContextID, parentHandle.entityID) == OCT_errorID) {
        return false;
    }
    return true;
}
OCT_ID iOCT_transform2D_add(OCT_ID contextID, OCT_ID entityID) {
    OCT_ID newID;
    OCT_index newIndex;
    iOCT_transform2D* newTransform;

    iOCT_entity* entity = iOCT_entity_get(contextID, entityID);
    iOCT_transform2D* parentTransform;
    int parentDepth;
    if (entityID == iOCT_ROOT_ID) {
        parentDepth = -1;
    }
    else {
        parentTransform = iOCT_transform2D_get(contextID, iOCT_entity_get(contextID, iOCT_entity_get(contextID, entityID)->parentID)->transformID);
        parentDepth = parentTransform->depth;
    }

    newTransform = iOCT_pool_push(contextID, OCT_typeComponentTransform2D, &newIndex);
    iOCT_registry_addEntry(contextID, entityID, OCT_typeComponentTransform2D, newIndex);

    // Set values
    newTransform->transformID = newID;
    newTransform->entityID = entityID;
    newTransform->depth = parentDepth + 1;
    newTransform->position = (OCT_vec2){iOCT_DEFAULT_POSITION_X, iOCT_DEFAULT_POSITION_Y};
    newTransform->rotation = iOCT_DEFAULT_ROTATION;
    newTransform->scale = (OCT_vec2){iOCT_DEFAULT_SCALE_X, iOCT_DEFAULT_SCALE_Y};

    // Link to parent
    iOCT_entity_updateMask(contextID, entityID, OCT_typeComponentTransform2D);

    iOCT_transform2D_sort(contextID, *newTransform);
    // printf("ADD transform2D %5" PRIu64 " to entity %" PRIu64 " in entityContext %" PRIu64 "\n", newID, entityID, contextID);
    return newID;
}

static void iOCT_transform2D_sort(OCT_ID contextID, iOCT_transform2D newTransform) {
    int newDepth = newTransform.depth;

    iOCT_transform2D* poolArray = (iOCT_transform2D*)iOCT_pool_get(contextID, OCT_typeComponentTransform2D)->data;
    OCT_index targetIndex;

    int workingDepth = newDepth;
    iOCT_transform2D workingTransform = newTransform;
    iOCT_transform2D displacedTransform;

    if (newDepth == currentMaxDepth) {
        depthEnds[newDepth] += 1;
        poolArray[depthEnds[newDepth]] = newTransform;  // replace anyway
        iOCT_registry_addEntry(contextID, newTransform.transformID, depthEnds[newDepth]);
        return;
    }
    if (newDepth > currentMaxDepth) {
        if (currentMaxDepth < 0) {
            depthEnds[newDepth] = 0;
        }
        else {
            depthEnds[newDepth] = depthEnds[currentMaxDepth] + 1;
        }
        poolArray[depthEnds[newDepth]] = newTransform;  // replace anyway
        iOCT_registry_addEntry(contextID, newTransform.transformID, depthEnds[newDepth]);
        currentMaxDepth = newDepth;
        return;
    }
    while (workingDepth < currentMaxDepth) {
        targetIndex = depthEnds[workingDepth] + 1;      // start of the next depth
        displacedTransform = poolArray[targetIndex];    // temp copy of the displaced

        poolArray[targetIndex] = workingTransform;      // copy the new one in
        iOCT_registry_addEntry(contextID, workingTransform.transformID, targetIndex);

        workingTransform = displacedTransform;          // start doing the same to the next layer
        depthEnds[workingDepth] += 1;                   // expand the depth group by 1
        workingDepth += 1;
    }
    OCT_index finalIndex = depthEnds[currentMaxDepth] + 1;
    poolArray[finalIndex] = workingTransform;
    iOCT_registry_addEntry(contextID, workingTransform.transformID, finalIndex);
    depthEnds[currentMaxDepth] += 1;
}

/// <summary>
/// Moves an entity by a given vector using its transform component.
/// </summary>
/// <param name="parentHandle"></param>
/// <param name="delta"></param>
/// <returns></returns>
OCT_vec2 OCT_transform2D_moveBy(OCT_entityHandle parentHandle, OCT_vec2 delta) {
    OCT_ID transformID = iOCT_entity_get(parentHandle.entityContextID, parentHandle.entityID)->transformID;
    return iOCT_transform2D_moveBy(parentHandle.entityContextID, transformID, delta);
}

OCT_vec2 iOCT_transform2D_moveBy(OCT_ID entityContextID, OCT_ID transformID, OCT_vec2 delta) {
    iOCT_transform2D* transform = iOCT_transform2D_get(entityContextID, transformID);
    transform->position = OCT_vec2_add(transform->position, delta);
    // printf("MOV transform2D %5" PRIu64 " to (%.4f, %.4f) in entityContext %" PRIu64 "\n", transformID, transform->position.x, transform->position.y, entityContextID);
    return transform->position;
}


/// <summary>
/// Rotates an entity by a given angle in degrees using its transform component. 
/// </summary>
/// <param name="parentHandle"></param>
/// <param name="deltaDegrees"></param>
/// <returns></returns>
float OCT_transform2D_rotateByDeg(OCT_entityHandle parentHandle, float deltaDegrees) {
    OCT_ID transformID = iOCT_entity_get(parentHandle.entityContextID, parentHandle.entityID)->transformID;
    return OCT_rad2deg(iOCT_transform2D_rotateBy(parentHandle.entityContextID, transformID, OCT_deg2rad(deltaDegrees)));
}
/// <summary>
/// Rotates an entity by a given angle in radians using its transform component.
/// </summary>
/// <param name="parentHandle"></param>
/// <param name="deltaRadians"></param>
/// <returns></returns>
float OCT_transform2D_rotateByRad(OCT_entityHandle parentHandle, float deltaRadians) {
    OCT_ID transformID = iOCT_entity_get(parentHandle.entityContextID, parentHandle.entityID)->transformID;
    return iOCT_transform2D_rotateBy(parentHandle.entityContextID, transformID, deltaRadians);
}
float iOCT_transform2D_rotateBy(OCT_ID entityContextID, OCT_ID transformID, float deltaRad) {
    iOCT_transform2D* transform = iOCT_transform2D_get(entityContextID, transformID);
    transform->rotation += deltaRad;  //NOTE_FOR_CCW_UNSURE_WHY

    transform->rotation = fmodf(transform->rotation, OCT_2PI_f);  // normalize to [0, 2pi]
    if (transform->rotation < 0) {
        transform->rotation += OCT_2PI_f;
    }
          
    return transform->rotation;
}

OCT_vec2 OCT_transform2D_scaleBy(OCT_entityHandle parentHandle, OCT_vec2 delta) {
    OCT_ID transformID = iOCT_entity_get(parentHandle.entityContextID, parentHandle.entityID)->transformID;
    return iOCT_transform2D_scaleBy(parentHandle.entityContextID, transformID, delta);
}
OCT_vec2 iOCT_transform2D_scaleBy(OCT_ID contextID, OCT_ID transformID, OCT_vec2 delta) {
    iOCT_transform2D* transform = iOCT_transform2D_get(contextID, transformID);
    transform->scale = OCT_vec2_add(transform->scale, delta);
    return transform->position;
}

static OCT_mat3 iOCT_transform2D_generateMatrix(iOCT_transform2D transform) {
    float cos = cosf(transform.rotation);
    float sin = sinf(transform.rotation);
    float scaleX = transform.scale.x;
    float scaleY = transform.scale.y;

    OCT_mat3 localMatrix = {
        scaleX * cos, -scaleY * sin, transform.position.x,
        scaleX * sin,  scaleY * cos, transform.position.y,
        0,             0,            1
    };
    return localMatrix;
}

void iOCT_transform2D_propagate(OCT_ID contextID) {
    iOCT_pool* pool = iOCT_pool_get(contextID, OCT_typeComponentTransform2D);
    iOCT_transform2D* array = (iOCT_transform2D*)pool->data;

    iOCT_transform2D* currentTransform;
    iOCT_transform2D* parentTransform;

    OCT_index rootIndex = iOCT_ROOT_ID;
    currentTransform = &array[rootIndex];
    currentTransform->localMatrix = iOCT_transform2D_generateMatrix(*currentTransform);
    currentTransform->globalMatrix = currentTransform->localMatrix;

    for (OCT_index index = rootIndex + 1; index < pool->count; index++) {
        currentTransform = &array[index];
        parentTransform = iOCT_transform2D_get(contextID, iOCT_entity_getParent(contextID, currentTransform->entityID)->transformID);

        currentTransform->localMatrix = iOCT_transform2D_generateMatrix(*currentTransform);
        currentTransform->globalMatrix = OCT_mat3_mul(parentTransform->globalMatrix, currentTransform->localMatrix);
        
    }

}

static iOCT_transform2D iOCT_transform2D_getParentU(OCT_ID contextID, OCT_ID entityID) {
    iOCT_entityContext* context = iOCT_entityContext_get(contextID);
    iOCT_registry* registry = &context->registry;
    iOCT_pool* pool = &context->pools[OCT_typeComponentTransform2D];

    OCT_ID entityID
}

OCT_vec2 iOCT_transform2D_globalPos(iOCT_transform2D transform) {
    OCT_mat3 matrix = transform.globalMatrix;
    OCT_vec2 globalPos = {
        .x = matrix.r0c2,
        .y = matrix.r1c2
    };
    return globalPos;
}



