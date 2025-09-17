#pragma once
#include "math/vectors.h"

#define DEFAULT_HITBOX_X 1.0f
#define DEFAULT_HITBOX_Y 1.0f

#define DEFAULT_MAX_HITBOXES 1024

typedef struct {
	size_t poolIndex;
	size_t parentIndex;

	point2D origin; // center
	vector2D bottomLeft; // to create the lines
} hitBox2D;

extern hitBox2D hitBox2DPool;
extern size_t hitBox2DCounter;

typedef struct {
	size_t poolIndex;
	size_t hitBoxIndex;

	point2D origin;
	point2D bottomLeft;
	point2D bottomRight;
	point2D topRight;
	point2D topLeft;
} hitBoxVertices;

extern hitBox2D hitBox2DPool;
extern size_t hitBox2DCounter;

size_t hitBox2DAddNew(size_t parentIndex);
void hitBox2DResize(size_t hitBoxIndex, size_t sizeX, size_t sizeY);