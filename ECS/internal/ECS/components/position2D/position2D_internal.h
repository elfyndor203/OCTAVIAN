#pragma once
#include "standards/ECSStandards_internal.h"

#include "OCT_Math.h"
#include "ECS/entity/entity_internal.h"

#define iOCT_POSITION2D_FAILED OCT_GENERIC_FAIL

#define DEFAULT_POSITION_X 0
#define DEFAULT_POSITION_Y 0

typedef struct iOCT_position2D{
	iOCT_componentID positionID;
	iOCT_entityID parentID;

	OCT_vector2D globalPosition2D;
	OCT_vector2D localPosition2D;
} iOCT_position2D;

iOCT_position2D* iOCT_position2D_get(iOCT_entitySetID entitySetID, iOCT_entityID parentID);
iOCT_position2D* iOCT_position2D_getPool(iOCT_entitySetID entitySetID);
OCT_counter* iOCT_position2D_getCounter(iOCT_entitySetID entitySetID);
iOCT_componentID iOCT_position2D_addNew(iOCT_entitySetID entitySetID, iOCT_entityID parentID);

void iOCT_position2D_move(iOCT_entitySetID entitySetID, iOCT_entityID parentID, OCT_vector2D distance);

