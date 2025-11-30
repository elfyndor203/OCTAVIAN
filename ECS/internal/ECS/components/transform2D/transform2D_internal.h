#pragma once
#include "ECS/components/transform2D/transform2D.h"
#include "standards/ECSStandards_internal.h"
#include "ECS/gameObject/gameObject_internal.h"

#define iOCT_TRANSFORM2D_FAILED GENERIC_FAIL

extern size_t iOCT_MAX_TRANSFORM2D;

typedef struct iOCT_transform2D {
	iOCT_componentID transformID;
	iOCT_gameObjectID parentID;

	float rotation;
	OCT_vector2D scale;
} iOCT_transform2D;

iOCT_transform2D* iOCT_transform2D_get(iOCT_sceneID sceneID, iOCT_gameObjectID parentID);
iOCT_transform2D* iOCT_transform2D_getPool(iOCT_sceneID sceneID);
iOCT_counter* iOCT_transform2D_getCounter(iOCT_sceneID sceneID);

iOCT_componentID transform2D_addNew(iOCT_sceneID sceneID, iOCT_gameObjectID parentID);

