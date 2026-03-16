#pragma once
#include "OCT_Math.h"

#include "ECS/entityContext/entityContext_internal.h"

typedef struct iOCT_module_ECS {
	OCT_pool contextPool;
	OCT_IDMap IDMap;
} iOCT_module_ECS;

extern iOCT_module_ECS iOCT_ECS_instance;	// Current running ECS

void iOCT_ECSModule_init();
void iOCT_ECSModule_free(iOCT_module_ECS* ECSModule);