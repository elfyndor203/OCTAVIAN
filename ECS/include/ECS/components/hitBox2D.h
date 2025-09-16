#pragma once
#include "math/vectors.h"

#define DEFAULT_HITBOX_X 1.0f
#define DEFAULT_HITBOX_Y 1.0f

typedef struct {
	size_t poolIndex;
	size_t parentIndex;

	vector2D origin; // center
	float width;
	float height;

	vector2D bottom;
	vector2D right;
	vector2D top;
	vector2D left;
} hitBox2D;

hitBox2D hitBox2DPool[DEFAULT_MAX_COMPONENTS_PER_TYPE];
size_t hitBox2DCounter;

size_t addNewHitBox2D(size_t parentIndex);
void resizeHitBox2D(size_t hitBoxIndex, size_t sizeX, size_t sizeY);