#pragma once
#include "OCT_Math.h"
#include "OCT_ECS.h"

#include "ECS/types_internal.h"

// Unique location within an entityContext
struct iOCT_uniqueIndex {
	OCT_index index;
	OCT_types componentType;
};

/// <summary>
/// Maps hold lists of pool array locations, indexed by ID
/// </summary>
struct iOCT_IDMap {
	OCT_ID entityContextID;	// Context that owns this map
	OCT_counter count;
	iOCT_uniqueIndex* array;				// array of unique indices
};

iOCT_IDMap* iOCT_IDMap_get(iOCT_entityContext* context);
bool iOCT_IDMap_allocate(iOCT_entityContext* context);
OCT_ID iOCT_IDMap_registerID(iOCT_entityContext* context, OCT_types componentType);
void iOCT_IDMap_remap(iOCT_entityContext* context, OCT_ID ID, OCT_index newIndex);
OCT_index iOCT_IDMap_getIndex(iOCT_entityContext* context, OCT_ID ID);