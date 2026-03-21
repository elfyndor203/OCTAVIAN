#pragma once
#include "resources/types_internal.h"

#include "cOCT_EngineStructure.h"

#include "resources/resourceList/resourceList_internal.h"

#define iOCT_RESOURCE_PATHNAME_MAX 64

struct iOCT_resource {
	OCT_ID listID;
	char path[iOCT_RESOURCE_PATHNAME_MAX];
	OCT_ID resourceID;
	iOCT_resourceType type;
};