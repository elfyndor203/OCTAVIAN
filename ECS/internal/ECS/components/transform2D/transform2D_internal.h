#pragma once
#include "ECS/components/transform2D/transform2D.h"
#include "standards/ECSStandards_internal.h"

#include "OCT_Math.h"
#include "ECS/entity/entity_internal.h"

#define iOCT_TRANSFORM2D_FAILED OCT_GENERIC_FAIL

#define DEFAULT_ROTATION 0.0f
#define DEFAULT_SCALE_X 1.0f
#define DEFAULT_SCALE_Y 1.0f

extern size_t iOCT_MAX_TRANSFORM2D;

typedef struct iOCT_transform2D {
	iOCT_componentID transformID;
	iOCT_entityID parentID;

	float rotation;
	OCT_vector2D scale;
} iOCT_transform2D;

iOCT_transform2D* iOCT_transform2D_get(iOCT_entityContextID entitySetID, iOCT_entityID parentID);
iOCT_transform2D* iOCT_transform2D_getPool(iOCT_entityContextID entitySetID);
OCT_counter* iOCT_transform2D_getCounter(iOCT_entityContextID entitySetID);

iOCT_componentID iOCT_transform2D_addNew(iOCT_entityContextID entitySetID, iOCT_entityID parentID);
void iOCT_transform2D_rotate(iOCT_entityContextID entitySetID, iOCT_entityID parentID, float degrees);

