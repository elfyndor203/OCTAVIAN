#pragma once
#include "architecture/pools_core.h"
#include "types_core.h"

#include "OCT_Math.h"
#include <stdbool.h>

#define cOCT_POOLSIZE_DEFAULT 4

/// <summary>
/// Pools manage the arrays of data. Each entitySet can have at most 1 pool per type. The arrays are contigous and allocated when a new pool is created. 
/// </summary>
struct cOCT_pool {
	OCT_ID ownerID;

	OCT_counter count;
	OCT_counter capacity;

	size_t elementSize;
	void* array;
};

cOCT_pool cOCT_pool_init(OCT_ID ownerID, OCT_counter capacity, size_t elementSize);
/// <summary>
/// Returns a void* pointer to the pool slot to be written into.
/// </summary>
/// <param name="pool"></param>
/// <param name="outIndex"></param>
/// <returns></returns>
void* cOCT_pool_addEntry(cOCT_pool* pool, OCT_index* outIndex);
void* cOCT_pool_access(cOCT_pool* pool, OCT_index index);

void cOCT_pool_deleteEntry(cOCT_pool* pool, OCT_index index, bool compact);
void cOCT_pool_free(cOCT_pool* pool);