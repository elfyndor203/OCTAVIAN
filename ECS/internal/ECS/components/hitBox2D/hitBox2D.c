#include "hitBox2D_internal.h"
#include "OCT_EngineStructure.h"
#include "ECS/entityContext/entityContext_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <math.h>


size_t iOCT_hitBox2D_max = iOCT_ENTITY_DEFAULT_MAX;
OCT_vec2 iOCT_hitBox2D_default_size = { iOCT_HITBOX_DEFAULTSIZE_X, iOCT_HITBOX_DEFAULTSIZE_Y };

iOCT_hitBox2D* iOCT_hitBox2D_get(OCT_ID entityContextID, OCT_ID hitBoxID) {
    return (iOCT_hitBox2D*)iOCT_getByID(entityContextID, hitBoxID, OCT_typeComponentHitBox2D);
}

/// <summary>
/// Adds a new hitbox to the given entity. If the entity already has a hitbox, create a new entity as a child of the parent, then add a hitbox to the child. 
/// </summary>
/// <param name="entityHandle"></param>
/// <returns></returns>
OCT_entityHandle OCT_hitBox2D_add(OCT_entityHandle parentHandle) {
    if (OCT_entity_hasComponent(parentHandle, OCT_typeComponentHitBox2D)) {
        printf("\nEntity already has hitBox. Generating new entity.\n");
        OCT_entityHandle newEntity = OCT_entity_new(parentHandle);
        iOCT_hitBox2D_add(newEntity.entityContextID, newEntity.entityID);
        return newEntity;
    }
    else {
        iOCT_hitBox2D_add(parentHandle.entityContextID, parentHandle.entityID);
        return parentHandle;
    }
}
/// Adds or REPLACES a hitbox on the given entity. 
OCT_ID iOCT_hitBox2D_add(OCT_ID entityContextID, OCT_ID parentID) {
    OCT_ID newID;
    iOCT_hitBox2D* newHitBox;

    newID = iOCT_IDMap_registerID(entityContextID, OCT_typeComponentHitBox2D);
    newHitBox = iOCT_hitBox2D_get(entityContextID, newID);
    memset(newHitBox, 0, sizeof(iOCT_hitBox2D));
    
    // Set values
    newHitBox->hitBoxID = newID;
    newHitBox->parentID = parentID;
    newHitBox->localOrigin = OCT_vec2_zero;
    newHitBox->rotation = 0;
    // Link to parent
    iOCT_entity* parent = iOCT_entity_get(entityContextID, parentID);
    parent->hitBoxID = newID;
    iOCT_entity_updateMask(entityContextID, parentID, OCT_typeComponentHitBox2D);

    iOCT_hitBox2D_resizeTo(entityContextID, parentID, iOCT_hitBox2D_default_size);

    printf("ADD hitBox2D %8" PRIu64 " to entity %" PRIu64 " in entityContext %" PRIu64 "\n", newID, parentID, entityContextID);
    return newID;
}

/// <summary>
/// Resizes a given hitbox to a given x, y size
/// </summary>
/// <param name="parentHandle"></param>
/// <param name="size"></param>
void OCT_hitBox2D_resizeTo(OCT_entityHandle parentHandle, OCT_vec2 size) {
    if (iOCT_entity_hasComponent(parentHandle.entityContextID, parentHandle.entityID, OCT_typeComponentHitBox2D) == false) {
        OCT_logError(ERR_HITBOX2D_DOES_NOT_EXIST);
        return;
    }
    OCT_ID entityContextID = parentHandle.entityContextID;
    OCT_ID parentID = parentHandle.entityID;
    iOCT_hitBox2D_resizeTo(entityContextID, parentID, size);
//    _OCT_sendMessage(_OCT_Renderer, parentHandle, _OCT_hitBox2D_update, OCT_GENERIC_NONE, OCT_GENERIC_NONE);
}
OCT_vec2 iOCT_hitBox2D_resizeTo(OCT_ID entityContextID, OCT_ID parentID, OCT_vec2 newSize) {
    //printf("Resizing hitbox...\n");
    iOCT_entity* parent = iOCT_entity_get(entityContextID, parentID);
    OCT_ID hitBoxID = iOCT_entity_get(entityContextID, parentID)->hitBoxID;
	iOCT_hitBox2D_get(entityContextID, hitBoxID)->size.x = newSize.x;
	iOCT_hitBox2D_get(entityContextID, hitBoxID)->size.y = newSize.y;
    return newSize;
}

float iOCT_hitBox2D_rotateBy(OCT_ID entityContextID, OCT_ID parentID, float deltaDeg) {
    printf("Rotating hitbox...\n");
    
    float deltaRad = OCT_deg2rad(deltaDeg);
    iOCT_hitBox2D* hitBox = iOCT_hitBox2D_get(entityContextID, parentID);
    hitBox->rotation += deltaRad;
    hitBox->rotation = fmodf(hitBox->rotation, OCT_2PI_f);
    return hitBox->rotation;
}

OCT_rectangle2D iOCT_hitBox2D_generateVertices(OCT_ID entityContextID, OCT_ID parentID) {
    iOCT_hitBox2D* hitBox = iOCT_hitBox2D_get(entityContextID, parentID);

    OCT_vert2 globalCenter = OCT_vec2_add(iOCT_transform2D_get(entityContextID, parentID)->globalPosition, hitBox->localOrigin); // get absolute values NOTE_DOES_NOT_ACCOUNT_FOR_SCALE
    float globalRotation = iOCT_transform2D_get(entityContextID, parentID)->rotation + hitBox->rotation;
//    OCT_vector2D globalSize = OCT_vec2_vec2_mult(hitBox->size, iOCT_transform2D_get(entityContextID, parentID)->scale);

    OCT_rectangle2D newBox = OCT_rectangle2D_generate(globalCenter, iOCT_hitBox2D_get(entityContextID, parentID)->size, globalRotation);
    return newBox;
}