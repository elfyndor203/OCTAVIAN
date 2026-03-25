#pragma once

#include "OCT_Math.h"

void OCT_RENModule_init(OCT_vec2 coordinateScale);
void OCT_RENModule_update();

/// <summary>
/// Handle all incoming messages. Required between loading a texture and opening a layer. Required after loading more than 64 sprites at a time outside of the game loop. 
/// </summary>
void OCT_RENModule_flush();