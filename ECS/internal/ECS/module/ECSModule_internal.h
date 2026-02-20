#pragma once
#include "OCT_Math.h"

#include "ECS/entityContext/entityContext_internal.h"

typedef struct iOCT_manager_ECS {
	iOCT_entityContext* entityContextPool;
	OCT_index* entityContextMap;
	OCT_counter entityContextCounter;
} iOCT_manager_ECS;

extern iOCT_manager_ECS iOCT_ECS_instance;	// Current running ECS

void iOCT_startModule_ECS();
void iOCT_freeModule_ECS(iOCT_manager_ECS* ECSModule);