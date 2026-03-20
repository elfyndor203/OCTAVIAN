#pragma once
#include "linking/types_core.h"

#include "OCT_Math.h"

#define OCT_NULL_ID 0

/// <summary>
/// Maps hold lists of pool array locations, indexed by ID
/// </summary>
struct cOCT_IDMap {
	OCT_ID ownerID;	// Context that owns this map
	OCT_counter count;
	OCT_index* array;
};

cOCT_IDMap iOCT_IDMap_init(OCT_ID ownerID, OCT_counter capacity);
OCT_ID iOCT_IDMap_register(cOCT_IDMap* map, OCT_index index);
OCT_index iOCT_IDMap_deregister(cOCT_IDMap* map, OCT_ID ID);
OCT_ID iOCT_IDMap_remap(cOCT_IDMap* map, OCT_ID ID, OCT_index newIndex);
OCT_index iOCT_IDMap_getIndex(cOCT_IDMap* map, OCT_ID ID);
void iOCT_IDMap_free(cOCT_IDMap* map);