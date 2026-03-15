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
	pool.array = calloc(OCT_POOLSIZE_DEFAULT, elementSize);
	if (!pool.array) {
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
	}
	return pool;
}

void* OCT_pool_add(OCT_pool* pool, OCT_index* indexDest) {
	void* slot = OCT_pool_access(pool, pool->count);
	*indexDest = pool->count++;
	return slot;
}

void OCT_pool_delete(OCT_pool* pool, OCT_index index, bool compact) {
	void* entry = OCT_pool_access(pool, index);

	// if shuffling is needed
	if (index < pool->count - 1 && compact) {
		void* finalEntry = OCT_pool_access(pool, pool->count);
		memcpy(entry, finalEntry, pool->elementSize);
		memset(finalEntry, 0, pool->elementSize);
	}
	else {
		memset(entry, 0, pool->elementSize);
	}
	pool->count--;
}

void OCT_pool_free(OCT_pool* pool) {
	free(pool->array);
	pool->array = NULL;
}

void* OCT_pool_access(OCT_pool* pool, OCT_index index) {
	void* entry = (char*)pool->array + index * pool->elementSize;
	return entry;
}
