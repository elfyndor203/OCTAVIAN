#include "entitySet_internal.h"
#include <string.h>

#include "OCT_EngineStructure.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/components/position2D/position2D_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"

iOCT_entitySet iOCT_entitySetList[iOCT_ENTITYSET_DEFAULT_MAX];
OCT_counter iOCT_entitySetCounter = 0;
iOCT_pool iOCT_poolList[iOCT_ENTITYSET_DEFAULT_MAX * OCT_componentsTotal];
OCT_counter iOCT_poolCounter = 0;

static size_t iOCT_componentSizeList[OCT_componentsTotal] = { sizeof(iOCT_entity), sizeof(iOCT_position2D), sizeof(iOCT_transform2D), sizeof(iOCT_hitBox2D) };	//NOTE __MUST__ MATCH COMPONENTTYPES

iOCT_entitySet* iOCT_entitySet_get(iOCT_entitySetID entitySetID) {				// valid as long as the entitySet exists
	if (entitySetID >= iOCT_ENTITYSET_DEFAULT_MAX || entitySetID >= iOCT_poolCounter) {
		OCT_logError(ERR_ENTITYSET_DOES_NOT_EXIST);
		return NULL;
	}
	return &iOCT_entitySetList[entitySetID];
}

static iOCT_poolID iOCT_pool_new(iOCT_entitySet* entitySet, OCT_componentTypes componentType) {
	iOCT_pool newPool = { 0 };											// create and set values

	newPool.entitySetID = entitySet->entitySetID;
	newPool.poolID = iOCT_poolCounter;
	newPool.componentType = componentType;
	newPool.counter = 0;
	newPool.array = calloc(iOCT_POOLSIZE_DEFAULT, iOCT_componentSizeList[componentType]);
	if (!newPool.array) {
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
		return OCT_GENERIC_FAIL;
	}

	entitySet->pools[componentType] = newPool.poolID;	// log pool
	iOCT_poolList[newPool.poolID] = newPool;							
	iOCT_poolCounter += 1;
	return newPool.poolID;
}

static iOCT_entityID iOCT_rootEntity_new(iOCT_entitySet* entitySet) {
	iOCT_entity newRoot = { 0 };

	iOCT_pool* pool = &iOCT_poolList[entitySet->pools[OCT_componentEntity]];
	iOCT_entity* poolArray = (iOCT_entity*)pool->array;
	iOCT_entitySetID entitySetID = entitySet->entitySetID;

	iOCT_entityID entityID = iOCT_ROOT_DEFAULT;

	newRoot.entitySetID = entitySetID;
	newRoot.entityID = entityID;
	newRoot.is3D = false;
	newRoot.parentID = OCT_GENERIC_NONE;
	newRoot.positionID = iOCT_position2D_addNew(entitySetID, entityID);
	newRoot.transformID = iOCT_transform2D_addNew(entitySetID, entityID);
	newRoot.hitBoxID = OCT_GENERIC_NONE;

	poolArray[iOCT_ROOT_DEFAULT] = newRoot;
	pool->counter += 1;
	entitySet->rootEntityID = entityID;
	return entityID;
}

OCT_entityHandle iOCT_entitySet_new() {
	iOCT_entitySet newEntitySet = { 0 };					// create and log a new entitySet
	iOCT_entitySetID entitySetID = iOCT_entitySetCounter;
	iOCT_entitySetCounter += 1;
	newEntitySet.entitySetID = entitySetID;					// set first to ensure the rootEntity gets the correct info

	for (int component = 0; component < OCT_componentsTotal; component++) {			// create and log each pool type
		iOCT_pool_new(&newEntitySet, component);
	}
	iOCT_rootEntity_new(&newEntitySet);

	iOCT_entitySetList[entitySetID] = newEntitySet;		// store entitySet
	printf("Created entitySet with entitySetID %zu\n", entitySetID);

	OCT_entityHandle rootHandle = { newEntitySet.rootEntityID, entitySetID };
	return rootHandle;
}

void iOCT_globalLists_initialize() {
	memset(iOCT_entitySetList, 0, sizeof(iOCT_entitySetList));
	memset(iOCT_poolList, 0, sizeof(iOCT_poolList));
	printf("EntitySet and pool lists zeroed out\n");
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



