#pragma once
#include "resources/types_internal.h"

#include "cOCT_EngineStructure.h"

#include "resources/module/RESModule_internal.h"

struct iOCT_resourceList {
	OCT_ID listID;
	cOCT_IDMap map;
	cOCT_pool pool;
	iOCT_resourceType type;
};

iOCT_resourceList* iOCT_resourceList_get(OCT_ID listID);
OCT_ID iOCT_resourceList_open(iOCT_resourceType type);
void iOCT_resourceList_close(iOCT_resourceList* list);