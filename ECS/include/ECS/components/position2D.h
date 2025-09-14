#pragma once
#include "myStandards.h"
#include "math/vectors.h"

#define DEFAULT_POSITION2D_X 0
#define DEFAULT_POSITION2D_Y 0

typedef struct {
	size_t poolIndex;
	size_t parentIndex;

	vector2D globalPosition2D;
	vector2D localPosition2D;
} position2D;

position2D position2DPool[DEFAULT_MAX_COMPONENTS_PER_TYPE];
size_t position2DCounter;

size_t addNewPosition2D(size_t parentIndex);