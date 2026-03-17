#pragma once
#include "types.h"

#include "OCT_EngineStructure.h"

#include "module/RESModule_internal.h"

struct iOCT_resourceList {
	OCT_ID listID;
	OCT_IDMap map;
	OCT_pool pool;
	iOCT_resourceType type;
};

iOCT_resourceList* iOCT_resourceList_get(OCT_ID listID);
OCT_ID iOCT_resourceList_open(iOCT_resourceType type);
void iOCT_resourceList_close(iOCT_resourceList* list);