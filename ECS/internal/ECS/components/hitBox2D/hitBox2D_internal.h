#pragma once
#include "ECS/components/hitBox2D/hitBox2D.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"
#include "OCT_Math.h"

#define DEFAULT_HITBOX_X 1.0f
#define DEFAULT_HITBOX_Y 1.0f

#define DEFAULT_MAX_HITBOXES 1024

typedef struct hitBox2D{
	OCT_componentID poolIndex;			// own spot
	OCT_gameObjectID parentIndex;		// object spot
	OCT_subcomponentID verticesIndex;	// vertices spot

	OCT_vertex2D localOrigin;	// center
	OCT_vector2D size;			// width, height
} hitBox2D;



OCT_componentID hitBox2D_addNew(OCT_gameObjectID parentIndex);
void hitBox2D_resize(OCT_gameObjectID parentIndex, float sizeX, float sizeY);
