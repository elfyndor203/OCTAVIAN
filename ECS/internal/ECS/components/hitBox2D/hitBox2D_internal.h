#pragma once
#include "hitBox2D_internal.h"

#include "OCT_Math.h"
#include "ECS/entity/entity_internal.h"

#define iOCT_HITBOX2D_FAILED OCT_GENERIC_FAIL

#define DEFAULT_HITBOX_X 0.25f
#define DEFAULT_HITBOX_Y 0.25f

typedef struct iOCT_hitBox2D{
	iOCT_componentID hitBoxID;	// own spot
	iOCT_entityID parentID;		// entity spot

	OCT_vertex2D localOrigin;	// center
	OCT_vector2D size;			// width, height
	float rotation;			// relative to the entity
} iOCT_hitBox2D;

iOCT_hitBox2D* iOCT_hitBox2D_get(iOCT_entityContextID entitySetID, iOCT_entityID parentID);
iOCT_hitBox2D* iOCT_hitBox2D_getPool(iOCT_entityContextID entitySetID);
OCT_counter* iOCT_hitBox2D_getCounter(iOCT_entityContextID entitySetID);

iOCT_componentID iOCT_hitBox2D_addNew(iOCT_entityContextID entitySetID, iOCT_entityID parentID);
void iOCT_hitBox2D_resize(iOCT_entityContextID entitySetID, iOCT_entityID parentID, float sizeX, float sizeY);
void iOCT_hitBox2D_rotate(iOCT_entityContextID entitySetID, iOCT_entityID parentID, float rotation);

OCT_rectangle2D iOCT_hitBox2D_generateVertices(iOCT_entityContextID entitySetID, iOCT_entityID parentID);