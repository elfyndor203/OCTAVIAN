#pragma once
#include "standards/myStandards.h"

#include "math/vectors/vector2D/vector2D.h"

#define DELTA_TIME

typedef struct {
	size_t poolIndex;
	size_t parentIndex;

	vector2D velocity;
	vector2D acceleration;
	vector2D forceNet;
} physics2D;

//void position2D_update(gameObjectIndex parentIndex);