#pragma once
#include "ECS/components/position2D/position2D.h"
#include "standards/ECSStandards_internal.h"

typedef struct iOCT_position2D{
	size_t poolIndex;
	size_t parentIndex;

	OCT_vector2D globalPosition2D;
	OCT_vector2D localPosition2D;
} iOCT_position2D;

OCT_componentID position2D_addNew(OCT_gameObjectID parentIndex);

