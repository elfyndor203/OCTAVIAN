#pragma once
#include "ECS/components/hitBox2D/hitBox2D.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"
#include "OCT_Math.h"

#define DEFAULT_HITBOX_X 1.0f
#define DEFAULT_HITBOX_Y 1.0f

#define DEFAULT_MAX_HITBOXES 1024

typedef struct iOCT_hitBox2D{
	OCT_componentID poolIndex;
	OCT_gameObjectID parentIndex;
	OCT_subcomponentID verticesIndex;

	OCT_vertex2D localOrigin; // center
	OCT_vector2D size;
} iOCT_hitBox2D;



OCT_componentID hitBox2D_addNew(OCT_gameObjectID parentIndex);
void hitBox2D_resize(OCT_gameObjectID parentIndex, float sizeX, float sizeY);
