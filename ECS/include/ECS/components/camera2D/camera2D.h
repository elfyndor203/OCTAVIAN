#pragma once
#include "OCT_EngineStructure.h"
#include "OCT_Math.h"

OCT_handle OCT_camera2D_add(OCT_handle entity, OCT_vec2 position, OCT_vec2 zoom, float rotation);
void OCT_camera2D_setActive(OCT_handle entityHandle);