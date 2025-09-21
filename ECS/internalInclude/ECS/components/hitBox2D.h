#pragma once
#include "myStandards.h"
#include "math/vectors.h"

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

componentIndex hitBox2DAddNew(gameObjectIndex parentIndex);
void hitBox2DResize(gameObjectIndex parentIndex, float sizeX, float sizeY);

componentIndex hitBox2DGenerateVertices(gameObjectIndex parentIndex);