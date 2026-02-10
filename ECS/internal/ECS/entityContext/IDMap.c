#include "IDMap_internal.h"
#include "entityContext_internal.h"

static iOCT_IDMap failedMap = { OCT_GENERIC_FAIL, OCT_GENERIC_FAIL, NULL };

iOCT_IDMap* iOCT_IDMap_get(iOCT_ID entityContextID) {
	return &iOCT_entityContext_get(entityContextID)->IDmap;
}

bool iOCT_IDMap_allocate(iOCT_ID entityContextID) {
	iOCT_IDMap* map = iOCT_IDMap_get(entityContextID);

	map->entityContextID = entityContextID;
	map->counter = 0;
	map->array = calloc(iOCT_POOLSIZE_DEFAULT * OCT_componentsTotal, sizeof(OCT_index));
	if (!map->array) {
		return false;
	}
	return true;
}

/// <summary>
/// Generates an available ID for the entitySet. Entities and components must register an ID to be found later.
/// </summary>
//iOCT_ID iOCT_ID_new(iOCT_entityContext* entitySet, OCT_index index) {
//	iOCT_IDMap* map = &entitySet->IDmap;
//
//	OCT_counter newID = entitySet->IDmap.counter;
//	map->array[newID] = index;
//	map->counter += 1;
//}