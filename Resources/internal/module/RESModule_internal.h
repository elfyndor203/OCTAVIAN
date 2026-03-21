#pragma once
#include "resources/types_internal.h"

#include "cOCT_EngineStructure.h"

#include "resources/resourceList/resourceList_internal.h"

struct iOCT_RESModule {
	iOCT_resourceList imageList;
	iOCT_resourceList audioList;
};

extern iOCT_RESModule iOCT_RESModule_instance;

void iOCT_RESModule_init();
void iOCT_RESModule_free();
