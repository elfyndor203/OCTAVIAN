#pragma once
#include "ECS/components/transform2D/transform2D.h"

#include "OCT_Math.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/types_internal.h"

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
struct iOCT_transform2D {
	OCT_ID transformID;
	OCT_ID entityID;
	int depth;

	OCT_ID parentID;
	OCT_index parentCache;
	bool dirty;

	OCT_vec2 position;
	float rotation;
	OCT_vec2 scale;

	OCT_mat3 localMatrix;
	OCT_mat3 globalMatrix;
};

iOCT_transform2D* iOCT_transform2D_get(iOCT_entityContext* context, OCT_ID transformID);
OCT_ID iOCT_transform2D_add(iOCT_entityContext* context, OCT_ID parentID);
OCT_vec2 iOCT_transform2D_moveBy(iOCT_entityContext* context, OCT_ID transformID, OCT_vec2 delta);
OCT_vec2 iOCT_transform2D_moveTo(iOCT_entityContext* context, OCT_ID transformID, OCT_vec2 newPos);
float iOCT_transform2D_rotateBy(iOCT_entityContext* context, OCT_ID parentID, float deltaDegrees);
OCT_vec2 iOCT_transform2D_scaleBy(iOCT_entityContext* context, OCT_ID transformID, OCT_vec2 delta);
void iOCT_transform2D_propagate(iOCT_entityContext* context);

OCT_vec2 iOCT_transform2D_globalPos(iOCT_transform2D transform);
