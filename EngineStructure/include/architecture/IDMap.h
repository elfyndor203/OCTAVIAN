#pragma once
#include "OCT_Math.h"
#include "linking/engineLayout.h"

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
OCT_ID OCT_IDMap_registerID(OCT_IDMap* map, int type, OCT_index index);
OCT_ID OCT_IDMap_remap(OCT_IDMap* map, OCT_ID ID, OCT_index newIndex);
OCT_index OCT_IDMap_getIndex(OCT_IDMap* map, OCT_ID ID);