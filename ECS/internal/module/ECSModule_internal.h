#pragma once
#include "ECS/types_internal.h"

#include "cOCT_EngineStructure.h"

struct iOCT_ECSModule {
	cOCT_IDMap contextMap;
	cOCT_pool contextPool;

	cOCT_pool physicsDataPool;
};

extern iOCT_ECSModule iOCT_ECSModule_instance;	// Current running ECS

void iOCT_ECSModule_init();
void OCT_ECSModule_free();
void iOCT_ECSModule_update();