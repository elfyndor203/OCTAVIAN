#include "entitySet_internal.h"
#include <string.h>

#include "OCT_EngineStructure.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/components/position2D/position2D_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"

OCT_index iOCT_entitySetMap_default[iOCT_ENTITYSET_DEFAULT_MAX];
iOCT_entitySet iOCT_entitySetPool_default[iOCT_ENTITYSET_DEFAULT_MAX];
OCT_counter iOCT_entitySetCounter = 0;
static const iOCT_ECS iOCT_GAME_ECS = { 
	iOCT_entitySetMap_default, 
	iOCT_entitySetPool_default, 
	&iOCT_entitySetCounter };

static size_t iOCT_componentSizeList[OCT_componentsTotal] = { sizeof(iOCT_entity), sizeof(iOCT_position2D), sizeof(iOCT_transform2D), sizeof(iOCT_hitBox2D) };	//NOTE __MUST__ MATCH COMPONENTTYPES
static iOCT_pool failedPool = { OCT_GENERIC_FAIL, OCT_GENERIC_FAIL, NULL };
static iOCT_IDMap failedMap = { OCT_GENERIC_FAIL, OCT_GENERIC_FAIL, NULL };

iOCT_entitySet* iOCT_entitySet_get(iOCT_entitySetID entitySetID) {				// valid as long as the entitySet exists
	if (entitySetID >= iOCT_entitySetCounter) {
		OCT_logError(ERR_ENTITYSET_DOES_NOT_EXIST);
		return NULL;
	}
	OCT_index location = iOCT_GAME_ECS.iOCT_entitySetMap[entitySetID];
	return &iOCT_GAME_ECS.iOCT_entitySetPool[location];
}

/// <summary>
/// Allows creation of all pools without rewriting when new component types are added
/// </summary>
static iOCT_pool iOCT_pool_new(iOCT_entitySet* entitySet, OCT_componentTypes componentType) {
	iOCT_pool newPool = { 0 };											// create and set values

	newPool.entitySetID = entitySet->entitySetID;
	newPool.componentType = componentType;
	newPool.counter = 0;
	newPool.array = calloc(iOCT_POOLSIZE_DEFAULT, iOCT_componentSizeList[componentType]);
	if (!newPool.array) {
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
		return failedPool;
	}
	return newPool;
}

static iOCT_IDMap iOCT_IDMap_new(iOCT_entitySet* entitySet) {
	iOCT_IDMap newMap = { 0 };

	newMap.entitySetID = entitySet->entitySetID;
	newMap.counter = 0;
	newMap.array = calloc(iOCT_POOLSIZE_DEFAULT * OCT_componentsTotal, sizeof(OCT_index));

	if (!newMap.array) {
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
		return failedMap;
	}
	return newMap;
}

static iOCT_entityID iOCT_rootEntity_new(iOCT_entitySet* entitySet) {
	iOCT_entity newRoot = { 0 };

	iOCT_pool* pool = &entitySet->pools[OCT_componentEntity];
	iOCT_entitySetID entitySetID = entitySet->entitySetID;

	OCT_index index = pool->counter;
	iOCT_entityID entityID = iOCT_ID_new(entitySet, index);		// generates fresh ID
	iOCT_entity* poolArray = (iOCT_entity*)pool->array;			// casts and gets the entity array
	poolArray[index] = newRoot;									// stores the entity
	pool->counter += 1;											// increments the pool

	iOCT_entity* root = iOCT_entity_get(entitySetID, entityID);			// sets the default values
	root->entitySetID = entitySetID;
	root->entityID = entityID;
	root->is3D = false;
	root->parentID = OCT_GENERIC_NONE;
	root->positionID = iOCT_position2D_addNew(entitySetID, entityID);
	root->transformID = iOCT_transform2D_addNew(entitySetID, entityID);
	root->hitBoxID = OCT_GENERIC_NONE;

	return entityID;
}

/// <summary>
/// Generates an available ID for the entitySet. Entities and components must register an ID to be found later.
/// </summary>
iOCT_ID iOCT_ID_new(iOCT_entitySet* entitySet, OCT_index index) {
	iOCT_IDMap* map = &entitySet->IDmap;

	OCT_counter newID = entitySet->IDmap.counter;
	map->array[newID] = index;
	map->counter += 1;
}

/// <summary>
/// Generates a new fresh entitySet. Allocates pool and ID arrays, then returns the root entity handle for use. 
/// </summary>
OCT_entityHandle iOCT_entitySet_new() {
	iOCT_entitySet newEntitySet = { 0 };					// create and log a new entitySet
	iOCT_entitySetID entitySetID = (iOCT_ID)iOCT_entitySetCounter;
	iOCT_entitySetCounter += 1;
	newEntitySet.entitySetID = entitySetID;					// set first to ensure the rootEntity gets the correct info

	for (int component = 0; component < OCT_componentsTotal; component++) {			// create and log each pool type
		newEntitySet.pools[component] = iOCT_pool_new(&newEntitySet, component);
	}
	newEntitySet.IDmap = iOCT_IDMap_new(&newEntitySet);
	newEntitySet.rootEntityID = iOCT_rootEntity_new(&newEntitySet);

	iOCT_entitySetPool_default[entitySetID] = newEntitySet;		// store entitySet
	printf("Created entitySet with entitySetID %zu\n", entitySetID);

	OCT_entityHandle rootHandle = { newEntitySet.rootEntityID, entitySetID };
	return rootHandle;
}

void iOCT_globalLists_initialize() {
	memset(iOCT_entitySetPool_default, 0, sizeof(iOCT_entitySetPool_default));
	printf("EntitySet zeroed out\n");
}

iOCT_pool* iOCT_pool_get(iOCT_entitySetID entitySetID, OCT_componentTypes componentType) {	// If the set exists, get the poolID from it. If the pool exists, return it. 
	iOCT_entitySet* entitySet = iOCT_entitySet_get(entitySetID);
	if (entitySet == NULL) {
		return NULL;
	}
	
	iOCT_poolID poolID = entitySet->pools[componentType];
	if (poolID >= iOCT_ENTITYSET_DEFAULT_MAX * OCT_componentsTotal || poolID >= iOCT_poolCounter) {
		OCT_logError(ERR_POOL_DOES_NOT_EXIST);
		return NULL;
	} 
	return &iOCT_poolList[poolID];
}

OCT_counter* iOCT_counter_get(iOCT_entitySetID entitySetID, OCT_componentTypes componentType) {
	iOCT_pool* pool = iOCT_pool_get(entitySetID, componentType);
	if (pool == NULL) {
		return NULL;
	}

	return &pool->counter;
}



