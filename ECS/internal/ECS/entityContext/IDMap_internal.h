#pragma once
#include "standards/ECSStandards_internal.h"

#include "OCT_Math.h"

/// <summary>
/// Maps hold lists of pool array locations, indexed by ID
/// </summary>
typedef struct iOCT_IDMap {
	iOCT_ID entityContextID;
	OCT_counter counter;
	OCT_index array;				// array of indices
} iOCT_IDMap;