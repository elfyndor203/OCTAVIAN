#pragma once
#include "OCT_EngineStructure.h"
#include "OCT_Math.h"

OCT_entityHandle OCT_hitBox2D_add(OCT_entityHandle parentHandle);
void OCT_hitBox2D_resizeTo(OCT_entityHandle parentHandle, OCT_vec2 size);