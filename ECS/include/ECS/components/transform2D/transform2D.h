#pragma once
#include <stdbool.h>
#include "OCT_Math.h"
#include "OCT_EngineStructure.h"

bool OCT_transform2D_add(OCT_entityHandle parentHandle);
OCT_vector2D OCT_transform2D_moveBy(OCT_entityHandle parentHandle, OCT_vector2D delta);
float OCT_transform2D_rotateByDeg(OCT_entityHandle parentHandle, float deltaDegrees);
float OCT_transform2D_rotateByRad(OCT_entityHandle parentHandle, float deltaRadians);