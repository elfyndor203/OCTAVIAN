#pragma once
#include <stdbool.h>
#include "OCT_Math.h"
#include "OCT_engineStructure.h"

bool OCT_transform2D_add(OCT_handle parentHandle);
OCT_vec2 OCT_transform2D_moveBy(OCT_handle entity, OCT_vec2 delta);
OCT_vec2 OCT_transform2D_moveTo(OCT_handle entity, OCT_vec2 newPos);
float OCT_transform2D_rotateByDeg(OCT_handle entity, float deltaDegrees);
float OCT_transform2D_rotateByRad(OCT_handle entity, float deltaRadians);
OCT_vec2 OCT_transform2D_scaleBy(OCT_handle entity, OCT_vec2 delta);