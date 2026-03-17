#include "architecture/IDMap.h"
#include "linking/types.h"

#include "OCT_Errors.h"
#include <stdlib.h>
#include <string.h>

#define OCT_IDMAP_TYPECONTAINER SIZE_MAX

// Allocates initial memory for a single entityContext.
OCT_IDMap OCT_IDMap_init(OCT_ID ownerID, OCT_counter capacity) {
	OCT_IDMap map = { 0 };

	map.ownerID = ownerID;
	map.count = 1; // null ID
	map.array = calloc(capacity + 1, sizeof(OCT_index)); // account for null ID slot
	if (!map.array) {
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
	}
	return map;
}

// Registers the next available ID with the provided pool index for any new entity or component.
OCT_ID OCT_IDMap_register(OCT_IDMap* map, OCT_index index) {
	OCT_ID newID;

	newID = map->count;		// Grabs the next available ID
	map->count += 1;

	map->array[newID] = index;		// Registers the index with the ID
	return newID;							// only ID gets returned
}

/// <summary>
/// Deletes an ID mapping. Does not deal with free ID recycling yet
/// </summary>
/// <param name="map"></param>
/// <param name="ID"></param>
/// <returns></returns>
OCT_index OCT_IDMap_deregister(OCT_IDMap* map, OCT_ID ID) {
	OCT_index index;
	OCT_index* slot = &map->array[ID];
	index = *slot;
	memset(slot, 0, sizeof(OCT_index));
	
	return index;
}


OCT_ID OCT_IDMap_remap(OCT_IDMap* map, OCT_ID ID, OCT_index newIndex) {
	map->array[ID] = newIndex;
	return ID;
}

OCT_index OCT_IDMap_getIndex(OCT_IDMap* map, OCT_ID ID) {
	return map->array[ID];
}

void OCT_IDMap_free(OCT_IDMap* map) {
	free(map->array);
	map->array = NULL;
}