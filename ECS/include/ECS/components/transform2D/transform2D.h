#pragma once
#include <stdbool.h>
#include "OCT_Math.h"
#include "OCT_EngineStructure.h"

bool OCT_transform2D_add(OCT_engineHandle parentHandle);
OCT_vec2 OCT_transform2D_moveBy(OCT_engineHandle parentHandle, OCT_vec2 delta);
float OCT_transform2D_rotateByDeg(OCT_engineHandle parentHandle, float deltaDegrees);
float OCT_transform2D_rotateByRad(OCT_engineHandle parentHandle, float deltaRadians);
OCT_vec2 OCT_transform2D_scaleBy(OCT_engineHandle parentHandle, OCT_vec2 delta);