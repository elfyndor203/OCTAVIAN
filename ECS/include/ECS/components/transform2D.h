#pragma once
#include "myStandards.h"
#include "math/vectors.h"

#define DEFAULT_ROTATION 0.0f

#define DEFAULT_SCALE_X 1.0f
#define DEFAULT_SCALE_Y 1.0f

typedef struct {
	size_t poolIndex;
	size_t parentIndex;

	float rotation;
	vector2D scale;
} transform2D;

transform2D transform2DPool[DEFAULT_MAX_COMPONENTS_PER_TYPE];
size_t transform2DCounter;

size_t addNewTransform2D(size_t parentIndex);
