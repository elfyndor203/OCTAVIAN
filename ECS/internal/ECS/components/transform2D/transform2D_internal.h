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

#define iOCT_TRANSFORM_MAXDEPTH 16

/// <summary>
/// Transform component. Stores local values and a global matrix. 
/// </summary>
typedef struct iOCT_transform2D {
	OCT_ID transformID;
	OCT_ID entityID;
	int depth;

	OCT_vec2 position;
	float rotation;
	OCT_vec2 scale;

	OCT_mat3 localMatrix;
	OCT_mat3 globalMatrix;
} iOCT_transform2D;

iOCT_transform2D* iOCT_transform2D_get(OCT_ID contextID, OCT_ID transformID);
OCT_ID iOCT_transform2D_add(OCT_ID contextID, OCT_ID parentID);
OCT_vec2 iOCT_transform2D_moveBy(OCT_ID contextID, OCT_ID transformID, OCT_vec2 delta);
float iOCT_transform2D_rotateBy(OCT_ID contextID, OCT_ID parentID, float deltaDegrees);
OCT_vec2 iOCT_transform2D_scaleBy(OCT_ID contextID, OCT_ID transformID, OCT_vec2 delta);
void iOCT_transform2D_propagate(OCT_ID contextID);

OCT_vec2 iOCT_transform2D_globalPos(iOCT_transform2D transform);
