#pragma once
#include "OCT_Math.h"
#include "linking/engineLayout.h"

#define OCT_NULL_ID 0

// Unique location within an entityContext
struct OCT_uniqueIndex {
	OCT_index index;
	int type;
};

/// <summary>
/// Maps hold lists of pool array locations, indexed by ID
/// </summary>
struct OCT_IDMap {
	OCT_ID ownerID;	// Context that owns this map
	OCT_counter count;
	OCT_uniqueIndex* array;
};

OCT_IDMap OCT_IDMap_init(OCT_ID ownerID, OCT_counter capacity);
OCT_ID OCT_IDMap_register(OCT_IDMap* map, int type, OCT_index index);
OCT_index OCT_IDMap_deregister(OCT_IDMap* map, OCT_ID ID);
OCT_ID OCT_IDMap_remap(OCT_IDMap* map, OCT_ID ID, OCT_index newIndex);
OCT_index OCT_IDMap_getIndex(OCT_IDMap* map, OCT_ID ID);
void OCT_IDMap_free(OCT_IDMap* map);