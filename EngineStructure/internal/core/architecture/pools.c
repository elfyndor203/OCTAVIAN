#include "architecture/pools_core.h"
#include "linking/types_core.h"

#include "OCT_Errors.h"
#include "OCT_Math.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

/// <summary>
/// Allocates memory for a single pool. Allows creation of all pools without rewriting when new component types are added
/// </summary>
cOCT_pool cOCT_pool_init(OCT_ID ownerID, OCT_counter capacity, size_t elementSize) {
	cOCT_pool pool = { 0 };

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

/// <summary>
/// Returns a pointer to the empty pool slot. Use the index return to register an ID. Should be cast to the correct type for clarity. 
/// </summary>
/// <param name="pool"></param>
/// <param name="indexDest"></param>
/// <returns></returns>
void* cOCT_pool_addEntry(cOCT_pool* pool, OCT_index* outIndex) {
	void* slot = cOCT_pool_access(pool, pool->count);
	*outIndex = pool->count++;
	return slot;
}

void cOCT_pool_deleteEntry(cOCT_pool* pool, OCT_index index, bool compact) {
	void* entry = cOCT_pool_access(pool, index);

	// if shuffling is needed
	if (index < pool->count - 1 && compact) {
		void* finalEntry = cOCT_pool_access(pool, pool->count);
		memcpy(entry, finalEntry, pool->elementSize);
		memset(finalEntry, 0, pool->elementSize);
	}
	else {
		memset(entry, 0, pool->elementSize);
	}
	pool->count--;
}

void cOCT_pool_free(cOCT_pool* pool) {
	free(pool->array);
	pool->array = NULL;
}

void* cOCT_pool_access(cOCT_pool* pool, OCT_index index) {
	void* entry = (char*)pool->array + index * pool->elementSize;
	return entry;
}
