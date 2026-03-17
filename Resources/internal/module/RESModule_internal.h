#pragma once
#include "OCT_EngineStructure.h"

enum iOCT_resourceType {
	iOCT_resourceImage,
	iOCT_resourceAudio,

	iOCT_resourceTypes_total
};

extern OCT_module iOCT_RESModule_instance;

void iOCT_RESModule_init();
void iOCT_RESModule_free();

extern OCT_ID iOCT_resourceList_IDList[iOCT_resourceTypes_total];

