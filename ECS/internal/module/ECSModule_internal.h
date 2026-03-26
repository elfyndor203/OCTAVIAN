#pragma once
#include "cOCT_EngineStructure.h"

extern cOCT_module iOCT_ECSModule_instance;	// Current running ECS

void iOCT_ECSModule_init();
void OCT_ECSModule_free();
void iOCT_ECSModule_update();