#include "registry_internal.h"
#include "entityContext_internal.h"
#include "pools_internal.h"

#include <stdlib.h>
#include <assert.h>

typedef enum {
	iOCT_metaParent = 1,
	iOCT_metaIncludedTotal = OCT_typesTotal + 1
} iOCT_entityMeta;

static OCT_ID iOCT_registry_getFree(iOCT_registry* registry);

iOCT_registry* iOCT_registry_get(OCT_ID entityContextID) {
	return &iOCT_entityContext_get(entityContextID)->registry;
}

OCT_index* iOCT_registry_accessU(iOCT_registry* registry, OCT_ID entity, OCT_types componentType) {
	return &registry->map[entity * OCT_typesTotal + componentType];
}

// Allocates initial memory for a single entityContext.
bool iOCT_registry_allocate(OCT_ID entityContextID) {
	iOCT_registry* map = iOCT_registry_get(entityContextID);

	map->entityContextID = entityContextID;
	map->entityCount = 0;
	map->capacity = iOCT_POOLSIZE_DEFAULT;
	map->map = calloc(iOCT_POOLSIZE_DEFAULT * iOCT_metaIncludedTotal, sizeof(OCT_index));
	map->recycleList = calloc(iOCT_POOLSIZE_DEFAULT, sizeof(OCT_ID));
	map->recycleCount = 0;

	if (!map->map) {
		return false;
	}
	return true;
}

// Registers the next available ID for any new entity.
OCT_ID iOCT_registry_registerID(OCT_ID contextID) {
	OCT_ID newID;

	iOCT_registry* registry = iOCT_registry_get(contextID);
	newID = iOCT_registry_getFree(registry);		// Grabs the next available ID

	return newID;							// only ID gets returned
}

void iOCT_registry_addEntry(OCT_ID contextID, OCT_ID entityID, OCT_types componentType, OCT_index index) {
	iOCT_registry* registry = iOCT_registry_get(contextID);
	OCT_index* slot = iOCT_registry_accessU(registry, entityID, componentType);
	*slot = index;
}

static OCT_ID iOCT_registry_getFree(iOCT_registry* registry) {
	OCT_ID freeID;
	OCT_counter* recycle = &registry->recycleCount;
	if (*recycle > 0) {
		freeID = registry->recycleList[*recycle - 1];
		(*recycle)--;
	}
	else {
		assert(registry->entityCount < registry->capacity);
		freeID = registry->entityCount++;
	}
	return freeID;
}