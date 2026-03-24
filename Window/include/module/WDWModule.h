#pragma once

#include "OCT_Math.h"

void OCT_WDWModule_init(char* name, unsigned int sizeX, unsigned int sizeY, OCT_vec4 color);
void OCT_WDWModule_startFrame();
void OCT_WDWModule_endFrame();
bool OCT_window_closed();