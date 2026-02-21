#pragma once
#include "OCT_Math.h"
#include "OCT_ECS.h"

// Unique location within an entityContext
typedef struct iOCT_indexPair {
	OCT_index index;
	OCT_types componentType;
} iOCT_uniqueIndex;

/// <summary>
/// Maps hold lists of pool array locations, indexed by ID
/// </summary>
typedef struct iOCT_IDMap {
	OCT_ID entityContextID;	// Context that owns this map
	OCT_counter count;
	iOCT_uniqueIndex* array;				// array of unique indices
} iOCT_IDMap;

iOCT_IDMap* iOCT_IDMap_get(OCT_ID entityContextID);
bool iOCT_IDMap_allocate(OCT_ID entityContextID);
OCT_ID iOCT_IDMap_registerID(OCT_ID entityContextID, OCT_types componentType);