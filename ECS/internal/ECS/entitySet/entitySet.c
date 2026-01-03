#include "entitySet_internal.h"

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
		return GENERIC_FAIL;
	}
	return &iOCT_entitySetList[entitySetID];
}

static iOCT_poolID iOCT_pool_new(iOCT_entitySetID entitySetID, OCT_componentTypes componentType) {
	iOCT_pool newPool = { 0 };											// create and set values

	newPool.entitySetID = entitySetID;
	newPool.poolID = iOCT_poolCounter;
	newPool.componentType = componentType;
	newPool.counter = 0;
	newPool.pool = calloc(1, iOCT_componentSizeList[componentType]);
	if (!newPool.pool) {
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
		return GENERIC_FAIL;
	}

	iOCT_poolList[newPool.poolID] = newPool;							// log pool
	iOCT_poolCounter += 1;
	return newPool.poolID;
}

OCT_entityHandle iOCT_entitySet_new() {
	iOCT_entitySet* newEntitySet = { 0 };		// create and log a new entitySet

	for (int component = 0; component < OCT_componentsTotal; component++) {			// create and log each pool type
		newEntitySet->pools[component] = iOCT_pool_new(newEntitySet, component);
	}

	newEntitySet->entitySetID = iOCT_entitySetCounter;
	iOCT_entitySetCounter += 1;

	// root object creation
	iOCT_entity blankRootObject = { 0 };
	blankRootObject.hitBoxID = iOCT_NO_COMPONENT;		// NOTE_NEW_COMPONENTS
	blankRootObject.positionID = iOCT_position2D_addNew(newEntitySet->entitySetID, )
	blankRootObject.componentsMask |= (1ULL << OCT_componentEntity);
	blankRootObject.componentsMask |= (1ULL << OCT_componentPosition2D);
	blankRootObject.componentsMask |= (1ULL << OCT_componentTransform2D);
	newEntitySet->rootEntity = blankRootObject;

	iOCT_entitySetList[iOCT_entitySetCounter] = newEntitySet;		// store entitySet

	iOCT_entity_getPool(newEntitySet->entitySetID)[0] = blankRootObject;	// store root object in entitySet
	*iOCT_entity_getCounter(newEntitySet->entitySetID) += 1;

	iOCT_entitySetID entitySetID = iOCT_entitySetCounter;	//


	printf("Created entitySet with entitySetID %zu\n", entitySetID);
	return entitySetID;
}

void iOCT_entitySetList_initialize() {
	memset(iOCT_entitySetList, 0, sizeof(iOCT_entitySetList));
	printf("EntitySet pool zeroed out\n");
}

iOCT_pool* iOCT_pool_get(iOCT_entitySetID entitySetID, OCT_componentTypes componentType) {	// If the set exists, get the poolID from it. If the pool exists, return it. 
	iOCT_entitySet* entitySet = iOCT_entitySet_get(entitySetID);
	if (entitySet == NULL) {
		return NULL;
	}
	
	iOCT_poolID poolID = entitySet->pools[componentType];
	if (poolID >= iOCT_POOLCOUNT_DEFAULT_MAX || poolID >= iOCT_poolCounter) {
		return NULL;
	} 

	return iOCT_poolList[poolID];
}

OCT_counter* iOCT_counter_get(iOCT_entitySetID entitySetID, OCT_componentTypes componentType) {
	iOCT_pool* pool = iOCT_pool_get(entitySetID, componentType);
	if (pool == NULL) {
		return NULL;
	}

	return &pool->counter;
}



