#pragma once
#include "OCT_Math.h"

#include "ECS/entityContext/entityContext_internal.h"

typedef struct iOCT_module_ECS {
	OCT_pool contextPool;
	OCT_IDMap IDMap;
} iOCT_module_ECS;

extern iOCT_module_ECS iOCT_ECS_instance;	// Current running ECS

void iOCT_startModule_ECS();
void iOCT_freeModule_ECS(iOCT_module_ECS* ECSModule);