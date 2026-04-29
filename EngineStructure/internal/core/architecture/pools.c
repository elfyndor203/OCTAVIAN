#include "architecture/pools_core.h"
#include "types_core.h"

#include "OCT_Errors.h"
#include "OCT_Math.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <crtdbg.h>
#include <stdio.h>

/// <summary>
/// Allocates memory for a single pool. Allows creation of all pools without rewriting when new component types are added
/// </summary>
cOCT_pool cOCT_pool_init(OCT_ID ownerID, OCT_counter capacity, size_t elementSize) {
	cOCT_pool pool = { 0 };

	pool.ownerID = ownerID;					// set default values
	pool.count = 0;
	pool.capacity = capacity;
	pool.elementSize = elementSize;
	pool.array = calloc(capacity, elementSize);
	if (!pool.array) {
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
	}

	printf("Init pool of size: %zu\n", capacity * elementSize);
	return pool;
}

/// <summary>
/// Returns a pointer to the empty pool slot. Use the index return to register an ID. Should be cast to the correct type for clarity. 
/// </summary>
/// <param name="pool"></param>
/// <param name="indexDest"></param>
/// <returns></returns>
void* cOCT_pool_addEntry(cOCT_pool* pool, OCT_index* outIndex) {
	if (pool->count == pool->capacity) {
		printf("Realloc pool of size %zu", pool->capacity * pool->elementSize);

		void* newArray = realloc(pool->array, pool->elementSize * pool->capacity * 2);
		if (!newArray) {
			OCT_logError(EXIT_FAILED_TO_ALLOCATE);
			return NULL;
		}
		else {
			pool->array = newArray;
			pool->capacity *= 2;
			printf("%zu\n", pool->capacity * pool->elementSize);
		}
	}

	void* slot = cOCT_pool_access(pool, pool->count);
	if (outIndex) {
		*outIndex = pool->count++;
	}

	return slot;
}

OCT_ID cOCT_pool_deleteEntry(cOCT_pool* pool, OCT_index index, bool compact) {
	void* entry = cOCT_pool_access(pool, index);
	OCT_ID swappedID = OCT_ID_NULL;

	// if shuffling is needed
	if (index < pool->count - 1 && compact) {
		void* finalEntry = cOCT_pool_access(pool, pool->count);
		memcpy(entry, finalEntry, pool->elementSize);
		memset(finalEntry, 0, pool->elementSize);
		swappedID = *(OCT_ID*)entry; // return the ID that got swapped to update the IDmap
	}
	else {
		memset(entry, 0, pool->elementSize);
	}
	pool->count--;
	return swappedID;
}

void cOCT_pool_free(cOCT_pool* pool) {
	free(pool->array);
	pool->array = NULL;
}

void* cOCT_pool_access(cOCT_pool* pool, OCT_index index) {
	void* entry = (char*)pool->array + index * pool->elementSize;
	return entry;
}
