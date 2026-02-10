#include "entityContext_internal.h"
#include <string.h>

#include "OCT_EngineStructure.h"
#include "ECS/ECS/ECSModule_internal.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/components/position2D/position2D_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"


iOCT_entityContext* iOCT_entityContext_get(iOCT_ID entityContextID) {				// valid as long as the entitySet exists
	OCT_index index = iOCT_ECS_active->iOCT_entityContextMap[entityContextID];
	return &iOCT_ECS_active->iOCT_entityContextPool[index];
}

static iOCT_entityID iOCT_rootEntity_new(iOCT_entityContext* entitySet) {
	iOCT_entity newRoot = { 0 };

	iOCT_pool* pool = &entitySet->pools[OCT_componentEntity];
	iOCT_entityContextID entitySetID = entitySet->entityContextID;

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
/// Generates a new fresh entitySet. Allocates pool and ID arrays, then returns the root entity handle for use. 
/// </summary>
OCT_entityHandle iOCT_entityContext_open() {
	iOCT_entityContext newEntityContext = { 0 };					// create and log a new entitySet
	iOCT_entityContextID entitySetID = (iOCT_ID)iOCT_entityContextCounter;
	iOCT_entityContextCounter += 1;
	newEntityContext.entityContextID = entitySetID;					// set first to ensure the rootEntity gets the correct info

	for (int component = 0; component < OCT_componentsTotal; component++) {			// create and log each pool type
		newEntityContext.pools[component] = iOCT_pool_allocate(&newEntityContext, component);
	}
	newEntityContext.IDmap = iOCT_IDMap_allocate(&newEntityContext);
	newEntityContext.rootEntityID = iOCT_rootEntity_new(&newEntityContext);

	iOCT_entitySetPool_default[entitySetID] = newEntityContext;		// store entitySet
	printf("Created entitySet with entitySetID %zu\n", entitySetID);

	OCT_entityHandle rootHandle = { newEntityContext.rootEntityID, entitySetID };
	return rootHandle;
}

void* iOCT_getByID(iOCT_ID entityContextID, OCT_componentTypes componentType, iOCT_ID ID) {
	iOCT_pool* pool = iOCT_pool_get(entityContextID, componentType);
	iOCT_IDMap* map = iOCT_IDMap_get(entityContextID);
	OCT_index index = map->array[ID];
	return &pool[index];
}



