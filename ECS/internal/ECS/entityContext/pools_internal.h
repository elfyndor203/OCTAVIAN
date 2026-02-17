#pragma once
#include "OCT_Math.h"
#include "OCT_EngineStructure.h"

#define iOCT_POOLSIZE_DEFAULT 64

/// <summary>
/// Pools manage the arrays of data. Each entitySet can have at most 1 pool per type. The arrays are contigous and allocated when a new pool is created. 
/// </summary>
typedef struct iOCT_pool {
	OCT_ID entityContextID;
	OCT_types componentType;

	OCT_counter counter;
	OCT_counter capacity;

	size_t componentSize;
	void* array;
} iOCT_pool;

iOCT_pool* iOCT_pool_get(OCT_ID entityContextID, OCT_types componentType);
bool iOCT_pool_allocate(OCT_ID entityContextID, OCT_types componentType);