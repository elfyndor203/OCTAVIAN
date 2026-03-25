#pragma once
#include "ECS/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"
#include <stdbool.h>

struct iOCT_sprite2D {
	bool visible;
	OCT_ID spriteID;

	OCT_vec4 uv;
	OCT_vec4 color;
	OCT_vec2 dimensions;
	OCT_ID transform;

	OCT_handle layer;
};

OCT_ID iOCT_sprite2D_add(iOCT_entityContext* context, OCT_ID entityID, OCT_handle layer, OCT_vec4 color, OCT_vec4 uv, OCT_vec2 dimensions);