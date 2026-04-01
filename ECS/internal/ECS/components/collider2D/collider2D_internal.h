#pragma once
#include "cOCT_EngineStructure.h"

#include "ECS/components/collider2D/collider2D.h"
#include "ECS/types_internal.h"

struct iOCT_collider2D {
	OCT_shapes type;
};

iOCT_collider2D* iOCT_collider2D_get(iOCT_entityContext* context, OCT_ID colliderID);