#pragma once
#include "OCT_EngineStructure.h"
#include "types_internal.h"

struct iOCT_module_ECS {
	OCT_pool layerPool;
	OCT_IDMap IDMap;

};

extern iOCT_module_renderer iOCT_REN_instance;

void iOCT_startModule_REN();
void iOCT_freeModule_REN(iOCT_freeModule_REN* ECSModule);