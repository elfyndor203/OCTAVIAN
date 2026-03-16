#pragma once
#include "OCT_Math.h"
#include "linking/engineLayout.h"
#include "types.h"

#define OCT_POOLSIZE_DEFAULT 8
#define OCT_POOLTYPE_CONTAINER SIZE_MAX

/// <summary>
/// Pools manage the arrays of data. Each entitySet can have at most 1 pool per type. The arrays are contigous and allocated when a new pool is created. 
/// </summary>
struct OCT_pool {
	OCT_ID ownerID;

	OCT_counter count;
	OCT_counter capacity;

	size_t elementSize;
	void* array;
};

OCT_pool OCT_pool_init(OCT_ID ownerID, OCT_counter capacity, size_t size);
void* OCT_pool_addTo(OCT_pool* pool, OCT_index* index);
void* OCT_pool_access(OCT_pool* pool, OCT_index index);

void OCT_pool_delete(OCT_pool* pool, OCT_index index, bool compact);
void OCT_pool_free(OCT_pool* pool);