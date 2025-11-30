#pragma once
#include "ECS/components/transform2D/transform2D.h"
#include "standards/ECSStandards_internal.h"

typedef struct iOCT_transform2D {
	size_t poolIndex;
	size_t parentIndex;

	float rotation;
	OCT_vector2D scale;
} iOCT_transform2D;

OCT_componentID transform2D_addNew(OCT_gameObjectID parentIndex);
