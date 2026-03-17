#pragma once
#include "linking/types_core.h"

#include "OCT_Math.h"

#define OCT_NULL_ID 0

/// <summary>
/// Maps hold lists of pool array locations, indexed by ID
/// </summary>
struct iOCT_IDMap {
	OCT_ID ownerID;	// Context that owns this map
	OCT_counter count;
	OCT_index* array;
};

OCT_IDMap iOCT_IDMap_init(OCT_ID ownerID, OCT_counter capacity);
OCT_ID iOCT_IDMap_register(OCT_IDMap* map, OCT_index index);
OCT_index iOCT_IDMap_deregister(OCT_IDMap* map, OCT_ID ID);
OCT_ID iOCT_IDMap_remap(OCT_IDMap* map, OCT_ID ID, OCT_index newIndex);
OCT_index iOCT_IDMap_getIndex(OCT_IDMap* map, OCT_ID ID);
void iOCT_IDMap_free(OCT_IDMap* map);