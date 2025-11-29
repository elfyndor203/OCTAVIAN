#pragma once
#include "ECS/components/hitBox2D/hitBox2D.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"
#include "OCT_Math.h"

#define DEFAULT_HITBOX_X 10.0f
#define DEFAULT_HITBOX_Y 10.0f

#define DEFAULT_MAX_HITBOXES 1024

typedef struct hitBox2D{
	OCT_componentID poolIndex;
	OCT_gameObjectID parentIndex;
	OCT_subcomponentID verticesIndex;

	point2D localOrigin; // center
	vector2D size;
} hitBox2D;

typedef struct hitBox2DVertices{
	OCT_componentID poolIndex;
	OCT_componentID hitBoxIndex;

	point2D localOrigin;
	point2D bottomLeft;
	point2D bottomRight;
	point2D topRight;
	point2D topLeft;
} hitBox2DVertices;

OCT_componentID hitBox2D_addNew(OCT_gameObjectID parentIndex);
void hitBox2D_resize(OCT_gameObjectID parentIndex, float sizeX, float sizeY);
OCT_componentID hitBox2D_generateVertices(OCT_gameObjectID parentIndex);