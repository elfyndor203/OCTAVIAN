#pragma once
#include "ECS/components/position2D/position2D.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/gameObject/gameObject_internal.h"

#define iOCT_POSITION2D_FAILED GENERIC_FAIL

size_t iOCT_MAX_POSITION2D = iOCT_DEFAULT_MAX_GAMEOBJECTS;

typedef struct iOCT_position2D{
	iOCT_componentID positionID;
	iOCT_gameObjectID parentID;

	OCT_vector2D globalPosition2D;
	OCT_vector2D localPosition2D;
} iOCT_position2D;

OCT_componentID position2D_addNew(OCT_gameObjectID parentIndex);

