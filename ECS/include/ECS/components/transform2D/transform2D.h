#pragma once
#include <stdbool.h>
#include "OCT_Math.h"
#include "OCT_EngineStructure.h"

bool OCT_transform2D_add(OCT_handle parentHandle);
OCT_vec2 OCT_transform2D_moveBy(OCT_handle parentHandle, OCT_vec2 delta);
float OCT_transform2D_rotateByDeg(OCT_handle parentHandle, float deltaDegrees);
float OCT_transform2D_rotateByRad(OCT_handle parentHandle, float deltaRadians);
OCT_vec2 OCT_transform2D_scaleBy(OCT_handle parentHandle, OCT_vec2 delta);