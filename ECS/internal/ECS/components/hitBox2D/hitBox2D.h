#pragma once
#include "standards/myStandards.h"

#include "ECS/components/componentTypes/componentTypes.h"
#include "math/vectors/vector2D/vector2D.h"

#define DEFAULT_HITBOX_X 10.0f
#define DEFAULT_HITBOX_Y 10.0f

#define DEFAULT_MAX_HITBOXES 1024

typedef struct {
	componentIndex poolIndex;
	gameObjectIndex parentIndex;
	subcomponentIndex verticesIndex;

	point2D localOrigin; // center
	vector2D size;
} hitBox2D;

typedef struct {
	componentIndex poolIndex;
	componentIndex hitBoxIndex;

	point2D localOrigin;
	point2D bottomLeft;
	point2D bottomRight;
	point2D topRight;
	point2D topLeft;
} hitBox2DVertices;

componentIndex hitBox2D_addNew(gameObjectIndex parentIndex);
void hitBox2D_resize(gameObjectIndex parentIndex, float sizeX, float sizeY);

componentIndex hitBox2D_generateVertices(gameObjectIndex parentIndex);