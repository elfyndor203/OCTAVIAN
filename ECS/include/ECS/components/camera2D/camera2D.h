#pragma once
#include "OCT_EngineStructure.h"
#include "OCT_Math.h"

#define OCT_CAMERA2D_ZOOM_SPEED 0.001f

OCT_handle OCT_camera2D_add(OCT_handle entity, OCT_vec2 position, float zoom, float rotation);
void OCT_camera2D_setActive(OCT_handle entityHandle);
float OCT_camera2D_zoom(OCT_handle entityHandle, float factor);