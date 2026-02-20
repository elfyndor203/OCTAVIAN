#include "transform2D_internal.h"
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>


#include "OCT_Errors.h"
#include "OCT_EngineStructure.h"
#include "units/constants.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/entityContext/entityContext_internal.h"
#include "ECS/entityContext/IDMap_internal.h"

static size_t iOCT_MAX_TRANSFORM2D = iOCT_ENTITY_DEFAULT_MAX;
static OCT_vector2D defaultPosition = { iOCT_DEFAULT_POSITION_X, iOCT_DEFAULT_POSITION_Y };
static OCT_vector2D defaultScale = { iOCT_DEFAULT_SCALE_X, iOCT_DEFAULT_SCALE_Y };

iOCT_transform2D* iOCT_transform2D_get(OCT_ID entityContextID, OCT_ID transformID) {
    return iOCT_getByID(entityContextID, transformID, OCT_typeComponentTransform2D);
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
OCT_ID iOCT_transform2D_add(OCT_ID entityContextID, OCT_ID parentID) {
    OCT_ID newID;
    iOCT_transform2D* newTransform;

    newID = iOCT_IDMap_registerID(entityContextID, OCT_typeComponentTransform2D);
    newTransform = iOCT_transform2D_get(entityContextID, newID);
    memset(newTransform, 0, sizeof(iOCT_transform2D));

    // Set values
    newTransform->transformID = newID;
    newTransform->parentID = parentID;
    newTransform->localPosition = defaultPosition;
    newTransform->rotation = iOCT_DEFAULT_ROTATION;
    newTransform->scale = defaultScale;

    // Link to parent
    iOCT_entity* parent = iOCT_entity_get(entityContextID, parentID);
    parent->transformID = newID;
    iOCT_entity_updateMask(entityContextID, parentID, OCT_typeComponentTransform2D);

    printf("ADD transform2D %5" PRIu64 " to entity %" PRIu64 " in entityContext %" PRIu64 "\n", newID, parentID, entityContextID);
    return newID;
}


/// <summary>
/// Moves an entity by a given vector using its transform component.
/// </summary>
/// <param name="parentHandle"></param>
/// <param name="delta"></param>
/// <returns></returns>
OCT_vector2D OCT_transform2D_moveBy(OCT_entityHandle parentHandle, OCT_vector2D delta) {
    OCT_ID transformID = iOCT_entity_get(parentHandle.entityContextID, parentHandle.entityID)->transformID;
    printf("MOV transform2D %5" PRIu64 " to (%.4f, %.4f) in entityContext %" PRIu64 "\n", transformID, delta.x, delta.y, parentHandle.entityContextID);
    return iOCT_transform2D_moveBy(parentHandle.entityContextID, transformID, delta);
}

OCT_vector2D iOCT_transform2D_moveBy(OCT_ID entityContextID, OCT_ID transformID, OCT_vector2D delta) {
    iOCT_transform2D* transform = iOCT_transform2D_get(entityContextID, transformID);
    transform->localPosition = OCT_vec2_vec2_add(transform->localPosition, delta);
    transform->dirty = true;
    return transform->localPosition;
}


/// <summary>
/// Rotates an entity by a given angle in degrees using its transform component. 
/// </summary>
/// <param name="parentHandle"></param>
/// <param name="deltaDegrees"></param>
/// <returns></returns>
float OCT_transform2D_rotateByDeg(OCT_entityHandle parentHandle, float deltaDegrees) {
    return OCT_rad2deg(iOCT_transform2D_rotateBy(parentHandle.entityContextID, parentHandle.entityID, OCT_deg2rad(deltaDegrees)));
}
/// <summary>
/// Rotates an entity by a given angle in radians using its transform component.
/// </summary>
/// <param name="parentHandle"></param>
/// <param name="deltaRadians"></param>
/// <returns></returns>
float OCT_transform2D_rotateByRad(OCT_entityHandle parentHandle, float deltaRadians) {
    return iOCT_transform2D_rotateBy(parentHandle.entityContextID, parentHandle.entityID, deltaRadians);
}
float iOCT_transform2D_rotateBy(OCT_ID entityContextID, OCT_ID transformID, float deltaRad) {
    iOCT_transform2D* transform = iOCT_transform2D_get(entityContextID, transformID);
    transform->rotation += deltaRad;  //NOTE_FOR_CCW_UNSURE_WHY

    transform->rotation = fmodf(transform->rotation, OCT_2PI_f);  // normalize to [0, 2pi]
    if (transform->rotation < 0) {
        transform->rotation += OCT_2PI_f;
    }

    transform->dirty = true;           
    return transform->rotation;
}


OCT_vector2D iOCT_transform2D_getGlobal(OCT_ID entityContextID, OCT_ID transformID) {       // NOTE_ VERY BASIC RN NO ROTATION
    OCT_vector2D globalPos = { 0 };
    iOCT_transform2D* nextTransform = iOCT_transform2D_get(entityContextID, transformID);
    iOCT_entity* nextParent = iOCT_entity_get(entityContextID, nextTransform->parentID);

    while (nextTransform != NULL) {
        globalPos = OCT_vec2_vec2_add(globalPos, nextTransform->localPosition);
        nextParent = iOCT_entity_get(entityContextID, nextParent->parentID);
        nextTransform = iOCT_transform2D_get(entityContextID, nextParent->transformID);
    }
    return globalPos;
}


