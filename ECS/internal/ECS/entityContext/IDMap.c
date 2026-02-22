#include "IDMap_internal.h"
#include "entityContext_internal.h"
#include "pools_internal.h"
#include <stdlib.h>

static iOCT_IDMap failedMap = { OCT_GENERIC_FAIL, OCT_GENERIC_FAIL, NULL };

iOCT_IDMap* iOCT_IDMap_get(OCT_ID entityContextID) {
	return &iOCT_entityContext_get(entityContextID)->IDMap;
}

// Allocates initial memory for a single entityContext.
bool iOCT_IDMap_allocate(OCT_ID entityContextID) {
	iOCT_IDMap* map = iOCT_IDMap_get(entityContextID);

	map->entityContextID = entityContextID;
	map->count = 0;
	map->array = calloc(iOCT_POOLSIZE_DEFAULT * OCT_typesTotal, sizeof(iOCT_uniqueIndex));
	if (!map->array) {
		return false;
	}
	return true;
}

// Registers the next available ID with the provided pool index for any new entity or component.
OCT_ID iOCT_IDMap_registerID(OCT_ID contextID, OCT_types componentType) {
	OCT_ID newID;
	OCT_index newIndex;

	iOCT_IDMap* IDMap = iOCT_IDMap_get(contextID);
	iOCT_pool* pool = iOCT_pool_get(contextID, componentType);

	newID = IDMap->count;		// Grabs the next available ID
	IDMap->count += 1;
	newIndex = pool->count;
	pool->count += 1;

	iOCT_uniqueIndex uniqueIndex = {		// index stays with the map
		.componentType = componentType,
		.index = newIndex
	};

	IDMap->array[newID] = uniqueIndex;		// Registers the index with the ID
	return newID;							// only ID gets returned
}

void iOCT_IDMap_remap(OCT_ID contextID, OCT_ID ID, OCT_index newIndex) {
	iOCT_IDMap* IDMap = iOCT_IDMap_get(contextID);
	IDMap->array[ID].index = newIndex;
	return;
}