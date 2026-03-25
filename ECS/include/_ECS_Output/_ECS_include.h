#pragma once
#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"
#include <stdbool.h>

typedef struct {
	bool visible;
	OCT_mat3 transform;
	OCT_vec4 uv;
	OCT_vec4 color;
	OCT_vec2 dimensions;
	OCT_handle layer;
} _OCT_sprite2D_dataRequest;

OCT_mat3 _OCT_transform2D_getMatrix(OCT_handle transformHandle);

OCT_vec4 _OCT_sprite2D_getUV(OCT_handle spriteHandle);
OCT_vec4 _OCT_sprite2D_getColor(OCT_handle spriteHandle);
OCT_vec2 _OCT_sprite2D_getDimensions(OCT_handle spriteHandle);

OCT_counter _OCT_entityContext_getCount();
OCT_counter _OCT_sprite2D_getCount(OCT_index contextIndex);
_OCT_sprite2D_dataRequest _OCT_sprite2D_getData(OCT_index spriteIndex, OCT_index contextIndex);