#include "architecture/pools.h"
#include "types.h"

#include "OCT_Errors.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

/// <summary>
/// Allocates memory for a single pool. Allows creation of all pools without rewriting when new component types are added
/// </summary>
OCT_pool OCT_pool_init(OCT_ID ownerID, OCT_counter capacity, size_t elementSize) {
	OCT_pool pool = { 0 };

	pool.ownerID = ownerID;					// set default values
	pool.count = 0;
	pool.capacity = capacity;
	pool.elementSize = elementSize;
	pool.array = calloc(iOCT_POOLSIZE_DEFAULT, elementSize);
	if (!pool.array) {
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
	}
	return pool;
}

void* OCT_pool_getSlot(OCT_pool* pool, OCT_index* index) {
	void* slot = (char*)pool->array + pool->count * pool->elementSize;
	*index = pool->count++;
	return slot;
}