#pragma once
#include "ECS/components/transform2D/transform2D.h"

#include "OCT_Math.h"
#include "ECS/entity/entity_internal.h"

#define iOCT_TRANSFORM2D_FAILED OCT_GENERIC_FAIL

#define iOCT_DEFAULT_POSITION_X 0.0f
#define iOCT_DEFAULT_POSITION_Y 0.0f
#define iOCT_DEFAULT_ROTATION 0.0f
#define iOCT_DEFAULT_SCALE_X 1.0f
#define iOCT_DEFAULT_SCALE_Y 1.0f

extern size_t iOCT_MAX_TRANSFORM2D;

/// <summary>
/// Transform component. Stores local values and a global matrix. 
/// </summary>
typedef struct iOCT_transform2D {
	OCT_ID transformID;
	OCT_ID parentID;

	bool dirty;
	OCT_vector2D localPosition;
	OCT_vector2D globalPosition;
	float rotation;
	OCT_vector2D scale;
} iOCT_transform2D;

iOCT_transform2D* iOCT_transform2D_get(OCT_ID entityContextID, OCT_ID transformID);
OCT_ID iOCT_transform2D_add(OCT_ID entityContextID, OCT_ID parentID);
OCT_vector2D iOCT_transform2D_moveBy(OCT_ID entityContextID, OCT_ID transformID, OCT_vector2D delta);
float iOCT_transform2D_rotateBy(OCT_ID entityContextID, OCT_ID parentID, float deltaDegrees);

