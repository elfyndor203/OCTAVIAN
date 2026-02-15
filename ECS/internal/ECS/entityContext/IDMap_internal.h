#pragma once
#include "standards/ECSStandards_internal.h"

#include "OCT_Math.h"

// Unique location within an entityContext
typedef struct iOCT_indexPair {
	OCT_index index;
	OCT_types componentType;
} iOCT_uniqueIndex;

/// <summary>
/// Maps hold lists of pool array locations, indexed by ID
/// </summary>
typedef struct iOCT_IDMap {
	iOCT_ID entityContextID;	// Context that owns this map
	OCT_counter counter;
	iOCT_uniqueIndex* array;				// array of unique indices
} iOCT_IDMap;

iOCT_IDMap* iOCT_IDMap_get(iOCT_ID entityContextID);
bool iOCT_IDMap_allocate(iOCT_ID entityContextID);
iOCT_ID iOCT_IDMap_registerID(iOCT_ID entityContextID, OCT_types componentType);