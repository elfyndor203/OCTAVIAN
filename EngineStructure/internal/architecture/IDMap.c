#include "architecture/IDMap.h"
#include "types.h"

#include "OCT_Errors.h"
#include <stdlib.h>

// Allocates initial memory for a single entityContext.
OCT_IDMap OCT_IDMap_init(OCT_ID ownerID, OCT_counter capacity) {
	OCT_IDMap map = { 0 };

	map.ownerID = ownerID;
	map.count = 0;
	map.array = calloc(capacity, sizeof(OCT_uniqueIndex));
	if (!map.array) {
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
	}
	return map;
}

// Registers the next available ID with the provided pool index for any new entity or component.
OCT_ID OCT_IDMap_registerID(OCT_IDMap* map, int type, OCT_index index) {
	OCT_ID newID;

	newID = map->count;		// Grabs the next available ID
	map->count += 1;

	OCT_uniqueIndex uniqueIndex = {		// index stays with the map
		.type = type,
		.index = index
	};

	map->array[newID] = uniqueIndex;		// Registers the index with the ID
	return newID;							// only ID gets returned
}

OCT_ID OCT_IDMap_remap(OCT_IDMap* map, OCT_ID ID, OCT_index newIndex) {
	map->array[ID].index = newIndex;
	return ID;
}

OCT_index OCT_IDMap_getIndex(OCT_IDMap* map, OCT_ID ID) {
	return map->array[ID].index;
}