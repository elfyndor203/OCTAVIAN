#pragma once
#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"

OCT_mat3 _OCT_transform2D_getMatrix(OCT_handle transformHandle);

OCT_vec4 _OCT_sprite2D_getUV(OCT_handle spriteHandle);
OCT_vec4 _OCT_sprite2D_getColor(OCT_handle spriteHandle);
OCT_vec2 _OCT_sprite2D_getDimensions(OCT_handle spriteHandle);