#pragma once
#include "ECS/components/transform2D/transform2D.h"
#include "standards/ECSStandards_internal.h"

typedef struct transform2D {
	size_t poolIndex;
	size_t parentIndex;

	float rotation;
	vector2D scale;
} transform2D;

OCT_componentID transform2D_addNew(OCT_gameObjectID parentIndex);
