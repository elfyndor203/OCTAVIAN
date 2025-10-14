#pragma once
#include "standards/ECSStandards.h"

#include "math/vectors/vector2D/vector2D.h"

#define DEFAULT_POSITION2D_X 0
#define DEFAULT_POSITION2D_Y 0

typedef struct {
	size_t poolIndex;
	size_t parentIndex;

	vector2D globalPosition2D;
	vector2D localPosition2D;
} position2D;

componentIndex position2D_addNew(gameObjectIndex parentIndex);