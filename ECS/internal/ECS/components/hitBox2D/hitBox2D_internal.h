#pragma once
#include "OCT_EngineStructure.h"
#include "OCT_Math.h"
#include "ECS/entity/entity_internal.h"

#define iOCT_HITBOX2D_FAILED OCT_GENERIC_FAIL

#define iOCT_HITBOX_DEFAULTSIZE_X 0.25f
#define iOCT_HITBOX_DEFAULTSIZE_Y 0.25f

typedef struct iOCT_hitBox2D{
	OCT_ID hitBoxID;	// own spot
	OCT_ID parentID;		// entity spot

	OCT_vertex2D localOrigin;	// center
	OCT_vector2D size;			// width, height
	float rotation;			// relative to the entity
} iOCT_hitBox2D;


OCT_ID iOCT_hitBox2D_add(OCT_ID entityContextID, OCT_ID parentID);
OCT_vector2D iOCT_hitBox2D_resizeTo(OCT_ID entityContextID, OCT_ID parentID, OCT_vector2D newSize);
float iOCT_hitBox2D_rotateBy(OCT_ID entityContextID, OCT_ID parentID, float deltaDeg);

OCT_rectangle2D iOCT_hitBox2D_generateVertices(OCT_ID entityContextID, OCT_ID parentID);