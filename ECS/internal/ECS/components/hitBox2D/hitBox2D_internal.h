#pragma once
#include "OCT_EngineStructure.h"
#include "OCT_Math.h"
#include "ECS/entity/entity_internal.h"

#include "ECS/types_internal.h"

#define iOCT_HITBOX2D_FAILED OCT_GENERIC_FAIL

#define iOCT_HITBOX_DEFAULTSIZE_X 0.25f
#define iOCT_HITBOX_DEFAULTSIZE_Y 0.25f

struct iOCT_hitBox2D{
	OCT_ID hitBoxID;	// own spot
	OCT_ID parentID;		// entity spot

	OCT_vec2 localOrigin;	// center
	OCT_vec2 size;			// width, height
	float rotation;			// relative to the entity
};

iOCT_hitBox2D* iOCT_hitBox2D_get(iOCT_entityContext* context, OCT_ID hitBoxID);
OCT_ID iOCT_hitBox2D_add(iOCT_entityContext* context, OCT_ID parentID);
OCT_vec2 iOCT_hitBox2D_resizeTo(iOCT_entityContext* context, OCT_ID parentID, OCT_vec2 newSize);
float iOCT_hitBox2D_rotateBy(iOCT_entityContext* context, OCT_ID parentID, float deltaDeg);

OCT_rect2 iOCT_hitBox2D_generateVertices(iOCT_entityContext* context, OCT_ID parentID);