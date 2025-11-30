#pragma once
#include "ECS/components/position2D/position2D.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/gameObject/gameObject_internal.h"

#define iOCT_POSITION2D_FAILED GENERIC_FAIL

extern size_t iOCT_MAX_POSITION2D;

typedef struct iOCT_position2D{
	iOCT_componentID positionID;
	iOCT_gameObjectID parentID;

	OCT_vector2D globalPosition2D;
	OCT_vector2D localPosition2D;
} iOCT_position2D;

iOCT_position2D* iOCT_position2D_get(iOCT_sceneID sceneID, iOCT_gameObjectID parentID);
iOCT_position2D* iOCT_position2D_getPool(iOCT_sceneID sceneID);
iOCT_counter* iOCT_position2D_getCounter(iOCT_sceneID sceneID);
iOCT_componentID iOCT_position2D_addNew(iOCT_sceneID sceneID, iOCT_gameObjectID parentID);

