#pragma once
#include "cOCT_EngineStructure.h"

#include "OCT_Math.h"
#include "ECS/components/collider2D/collider2D.h"
#include "ECS/types_internal.h"

struct iOCT_collider2D {
	OCT_ID colliderID;
	OCT_shape2 shape;
};

iOCT_collider2D* iOCT_collider2D_get(iOCT_entityContext* context, OCT_ID colliderID);
OCT_ID iOCT_collider2D_add(iOCT_entityContext* context, OCT_ID entityID, OCT_shape2 shape);