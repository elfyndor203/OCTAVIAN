#pragma once
#include "myStandards.h"

#include "math/vectors.h"

#define DELTA_TIME

typedef struct physics2D {
	size_t poolIndex;
	size_t parentIndex;

	vector2D velocity;
	vector2D acceleration;
	vector2D forceNet;
};

void updatePosition2D(gameObjectIndex parentIndex);