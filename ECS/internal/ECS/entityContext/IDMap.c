#include "IDMap_internal.h"
#include "entityContext_internal.h"
#include "ECS/entity/entity_internal.h"
#include "pools_internal.h"
#include "OCT_Errors.h"
#include <stdlib.h>


iOCT_IDMap* iOCT_IDMap_get(OCT_ID entityContextID) {
	return &iOCT_entityContext_get(entityContextID)->IDMap;
}

// Allocates initial memory for a single context's entities.
bool iOCT_IDMap_allocate(OCT_ID entityContextID) {
	iOCT_IDMap* map = iOCT_IDMap_get(entityContextID);

	map->entityContextID = entityContextID;
	map->nextID = 0;
	map->map = malloc(iOCT_ENTITY_DEFAULT_MAX * (OCT_typesTotal + iOCT_metaCount) * sizeof(OCT_index));
	if (!map->map) {
		return false;
	}
	map->freeIDs = malloc(iOCT_ENTITY_DEFAULT_MAX * sizeof(OCT_ID));
	if (!map->freeIDs) {
		return false;
	}
	return true;
}

OCT_index* iOCT_IDMap_access(OCT_ID contextID, OCT_ID entityID, OCT_types componentType) {
	iOCT_IDMap* IDMap = iOCT_IDMap_get(contextID);
	return &IDMap->map[entityID * OCT_typesTotal + componentType];
}

static OCT_ID iOCT_IDmap_getFree(iOCT_IDMap* IDMap) {	// helper to recycle IDs
	OCT_ID freeID;
	OCT_counter* freeCount = &IDMap->freeCount;

	if (*freeCount > 0) {
		freeID = IDMap->freeIDs[*freeCount - 1];
		*freeCount -= 1;
		return freeID;
	}
	else {
		return IDMap->nextID++;
	}
}

// Registers the next available ID with the provided pool index for a new entity
OCT_ID iOCT_IDMap_register(OCT_ID contextID) {
	OCT_ID newID;
	OCT_index newIndex;

	iOCT_IDMap* IDMap = iOCT_IDMap_get(contextID);
	iOCT_pool* pool = iOCT_pool_get(contextID, OCT_typeEntity);

	newIndex = pool->count++;
	newID = iOCT_IDmap_getFree(IDMap);

	IDMap->map[newID] = newIndex;		// Registers the index with the ID
	return newID;							// only ID gets returned
}

void iOCT_IDMap_deregister(OCT_ID contextID, OCT_ID entityID) {
	iOCT_IDMap* map = iOCT_IDMap_get(contextID);
	map->freeIDs[map->freeCount++] = entityID;

	OCT_index* slot = iOCT_IDMap_access(contextID, entityID, OCT_typeEntity);
	*slot = OCT_GENERIC_NONE;
}

OCT_ID iOCT_IDMap_addComponent(OCT_ID contextID, OCT_ID entityID, OCT_types componentType) {
	OCT_index* slot = iOCT_IDMap_access(contextID, entityID, componentType);
	iOCT_pool* componentPool = iOCT_pool_get(contextID, componentType);
	OCT_index nextIndex = componentPool->count++;

	*slot = nextIndex;
}