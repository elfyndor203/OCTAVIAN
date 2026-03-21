#include "hitBox2D_internal.h"

#include "cOCT_EngineStructure.h"
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "ECS/entityContext/entityContext_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"

size_t iOCT_hitBox2D_max = iOCT_ENTITY_DEFAULT_MAX;
OCT_vec2 iOCT_hitBox2D_default_size = { iOCT_HITBOX_DEFAULTSIZE_X, iOCT_HITBOX_DEFAULTSIZE_Y };

iOCT_hitBox2D* iOCT_hitBox2D_get(iOCT_entityContext* context, OCT_ID hitBoxID) {
    return (iOCT_hitBox2D*)iOCT_getByID(context, hitBoxID, OCT_ECSType_hitBox2D);
}

/// <summary>
/// Adds a new hitbox to the given entity. If the entity already has a hitbox, create a new entity as a child of the parent, then add a hitbox to the child. 
/// </summary>
/// <param name="entityHandle"></param>
/// <returns></returns>
OCT_handle OCT_hitBox2D_add(OCT_handle entity) {
    assert(entity.type == OCT_handle_entity);

    iOCT_entityContext* context = iOCT_entityContext_get(entity.containerID);
    if (OCT_entity_hasComponent(entity, OCT_ECSType_hitBox2D)) {
        printf("\nEntity already has hitBox. Generating new entity.\n");
        OCT_handle newEntity = OCT_entity_new(entity);
        iOCT_hitBox2D_add(context, newEntity.objectID);
        return newEntity;
    }
    else {
        iOCT_hitBox2D_add(context, entity.objectID);
        return entity;
    }
}
/// Adds or REPLACES a hitbox on the given entity. 
OCT_ID iOCT_hitBox2D_add(iOCT_entityContext* context, OCT_ID parentID) {
    OCT_ID newID;
    OCT_index newIndex;
    iOCT_hitBox2D* newHitBox;

    newHitBox = (iOCT_hitBox2D*)cOCT_pool_addEntry(iOCT_pool_get(context, OCT_ECSType_hitBox2D), &newIndex);
    newID = cOCT_IDMap_register(&context->IDMap, newIndex);
    memset(newHitBox, 0, sizeof(iOCT_hitBox2D));
    
    // Set values
    newHitBox->hitBoxID = newID;
    newHitBox->parentID = parentID;
    newHitBox->localOrigin = OCT_vec2_zero;
    newHitBox->rotation = 0;
    // Link to parent
    iOCT_entity* parent = iOCT_entity_get(context, parentID);
    parent->hitBoxID = newID;
    iOCT_entity_updateMask(context, parentID, OCT_ECSType_hitBox2D);

    iOCT_hitBox2D_resizeTo(context, parentID, iOCT_hitBox2D_default_size);

    // printf("ADD hitBox2D %8" PRIu64 " to entity %" PRIu64 " in entityContext %" PRIu64 "\n", newID, parentID, entityContextID);
    return newID;
}

/// <summary>
/// Resizes a given hitbox to a given x, y size
/// </summary>
/// <param name="parentHandle"></param>
/// <param name="size"></param>
void OCT_hitBox2D_resizeTo(OCT_handle entity, OCT_vec2 size) {
    assert(entity.type == OCT_handle_entity);

    iOCT_entityContext* context = iOCT_entityContext_get(entity.containerID);
    if (iOCT_entity_hasComponent(context, entity.objectID, OCT_ECSType_hitBox2D) == false) {
        OCT_logError(ERR_HITBOX2D_DOES_NOT_EXIST);
        return;
    }
    OCT_ID entityContextID = entity.containerID;
    OCT_ID parentID = entity.objectID;
    iOCT_hitBox2D_resizeTo(context, parentID, size);
//    _OCT_sendMessage(_OCT_Renderer, parentHandle, _OCT_hitBox2D_update, OCT_GENERIC_NONE, OCT_GENERIC_NONE);
}
OCT_vec2 iOCT_hitBox2D_resizeTo(iOCT_entityContext* context, OCT_ID parentID, OCT_vec2 newSize) {
    //printf("Resizing hitbox...\n");
    iOCT_entity* parent = iOCT_entity_get(context, parentID);
    OCT_ID hitBoxID = iOCT_entity_get(context, parentID)->hitBoxID;
	iOCT_hitBox2D_get(context, hitBoxID)->size.x = newSize.x;
	iOCT_hitBox2D_get(context, hitBoxID)->size.y = newSize.y;
    return newSize;
}

float iOCT_hitBox2D_rotateBy(iOCT_entityContext* context, OCT_ID parentID, float deltaDeg) {
    printf("Rotating hitbox...\n");
    
    float deltaRad = OCT_deg2rad(deltaDeg);
    iOCT_hitBox2D* hitBox = iOCT_hitBox2D_get(context, parentID);
    hitBox->rotation += deltaRad;
    hitBox->rotation = fmodf(hitBox->rotation, OCT_2PI_f);
    return hitBox->rotation;
}

OCT_rect2 iOCT_hitBox2D_generateVertices(iOCT_entityContext* context, OCT_ID parentID) {
    iOCT_hitBox2D* hitBox = iOCT_hitBox2D_get(context, parentID);

    OCT_vec2 globalCenter = OCT_vec2_add(iOCT_transform2D_globalPos(*iOCT_transform2D_get(context, parentID)), hitBox->localOrigin);
    float globalRotation = iOCT_transform2D_get(context, parentID)->rotation + hitBox->rotation;
//    OCT_vector2D globalSize = OCT_vec2_vec2_mult(hitBox->size, iOCT_transform2D_get(entityContextID, parentID)->scale);

    OCT_rect2 newBox = OCT_rectangle2D_generate(globalCenter, iOCT_hitBox2D_get(context, parentID)->size, globalRotation);
    return newBox;
}