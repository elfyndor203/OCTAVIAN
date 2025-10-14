#pragma once
#include "standards/myStandards.h"

#include "math/vectors/vector2D/vector2D.h"

#define DEFAULT_ROTATION 0.0f

#define DEFAULT_SCALE_X 1.0f
#define DEFAULT_SCALE_Y 1.0f

typedef struct {
	size_t poolIndex;
	size_t parentIndex;

	float rotation;
	vector2D scale;
} transform2D;

componentIndex transform2D_addNew(gameObjectIndex parentIndex);
