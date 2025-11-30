#pragma once
#include "ECS/components/physics2D/physics2D.h"
#include "standards/ECSStandards_internal.h"

typedef struct {
	size_t poolIndex;
	size_t parentIndex;

	OCT_vector2D velocity;
	OCT_vector2D acceleration;
	OCT_vector2D forceNet;
} physics2D;

//void position2D_update(gameObjectIndex parentIndex);