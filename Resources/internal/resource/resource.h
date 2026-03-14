#pragma once
#include "OCT_EngineStructure.h"

typedef enum {
	OCT_resourceImage,
	OCT_resourceAudio
} OCT_resourceType;

typedef struct OCT_resourceHandle {
	OCT_ID resourceID;
	OCT_resourceType type;
} OCT_resourceHandle;