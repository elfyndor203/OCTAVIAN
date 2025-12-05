#pragma once
#include "standards/ECSStandards_internal.h"

#include "OCT_Math.h"
#include "ECS/components/componentTypes/componentTypes_internal.h"
#include "ECS/entity/entity_internal.h"

#define iOCT_HITBOX2D_FAILED GENERIC_FAIL

#define DEFAULT_HITBOX_X 1.0f
#define DEFAULT_HITBOX_Y 1.0f

typedef struct iOCT_hitBox2DVertices {
	OCT_vector2D origin;
	OCT_vector2D bottomLeft;
	OCT_vector2D bottomRight;
	OCT_vector2D topRight;
	OCT_vector2D topLeft;
} iOCT_hitBox2DVertices;

typedef struct iOCT_hitBox2D{
	iOCT_componentID hitBoxID;			// own spot
	iOCT_entityID parentID;		// object spot

	OCT_vertex2D localOrigin;	// center
	OCT_vector2D size;			// width, height

	iOCT_hitBox2DVertices boxVertices;
} iOCT_hitBox2D;

iOCT_hitBox2D* iOCT_hitBox2D_get(iOCT_entitySetID entitySetID, iOCT_entityID parentID);
iOCT_hitBox2D* iOCT_hitBox2D_getPool(iOCT_entitySetID entitySetID);
OCT_counter* iOCT_hitBox2D_getCounter(iOCT_entitySetID entitySetID);

iOCT_componentID iOCT_hitBox2D_addNew(iOCT_entitySetID entitySetID, iOCT_entityID parentID);
void iOCT_hitBox2D_resize(iOCT_entitySetID entitySetID, iOCT_entityID parentID, float sizeX, float sizeY);

void iOCT_hitBox2D_generateVertices(entitySetID, parentID);
