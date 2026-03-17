#pragma once
#include "types.h"

#include "OCT_EngineStructure.h"

#define iOCT_PATHNAME_MAX 64

struct iOCT_resource {
	OCT_ID listID;
	OCT_ID resourceID;
	char path[iOCT_PATHNAME_MAX];
	iOCT_resourceType type;
};