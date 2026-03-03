#pragma once
#include "OCT_EngineStructure.h"
#include "OCT_Math.h"

typedef struct iOCT_IDMap_new {
	OCT_ID contextID;
	OCT_counter entityCount;
	OCT_index* componentArray;
};