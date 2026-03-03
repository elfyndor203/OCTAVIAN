#include "entityContext_internal.h"
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

#include "OCT_EngineStructure.h"
#include "ECS/module/ECSModule_internal.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"


iOCT_entityContext* iOCT_entityContext_get(OCT_ID entityCtxID) {				// valid as long as the entityContext exists
	OCT_index index = iOCT_ECS_instance.entityContextMap[entityCtxID];
	return &iOCT_ECS_instance.entityContextPool[index];
}

/// <summary>
/// Opens a new entity context in the current ECS instance. Allocates initial needed memory and returns the root handle for use.
/// </summary>
/// <returns></returns>
OCT_entityHandle OCT_entityContext_open() {
	return iOCT_entityContext_open();
}

OCT_entityHandle iOCT_entityContext_open() {
	OCT_ID entityContextID = (OCT_ID)iOCT_ECS_instance.entityContextCounter;	// Count will always be the next available slot
	iOCT_ECS_instance.entityContextCounter += 1;
	iOCT_ECS_instance.entityContextMap[entityContextID] = (OCT_index)entityContextID; // ID will start the same as the index
	printf("Created entityContext with ID %" PRIu64 "\n", entityContextID);

	iOCT_entityContext* newEntityContext = iOCT_entityContext_get(entityContextID);	// get the next available slot in the entityContext pool

	newEntityContext->entityContextID = entityContextID;
	iOCT_IDMap_allocate(entityContextID);
	for (int poolType = 0; poolType < OCT_typesTotal; poolType++) {			// create and log each pool type
		iOCT_pool_allocate(entityContextID, poolType);
	}

	iOCT_entity_new(entityContextID, iOCT_NOPARENT);						// Create root entity
	OCT_entityHandle rootHandle = { entityContextID, iOCT_ROOT_ID };
	return rootHandle;
}

/// <summary>
/// Frees all memory used by the entityContext. Handles bookkeeping by swap replacing with the last entityContext if necessary. 
/// </summary>
/// <param name="closedContextID"></param>
void OCT_entityContext_close(OCT_entityHandle rootHandle) {
	iOCT_entityContext_close(rootHandle.entityContextID);
}
void iOCT_entityContext_close(OCT_ID closedContextID) {
	iOCT_manager_ECS* game = &iOCT_ECS_instance;
	iOCT_entityContext* closedContext = iOCT_entityContext_get(closedContextID);
	OCT_index closedContextIndex = game->entityContextMap[closedContextID];
	OCT_index lastContextIndex = game->entityContextCounter - 1;									
	OCT_ID lastContextID = game->entityContextPool[lastContextIndex].entityContextID;

	free(closedContext->IDMap.map);												// Free pool and IDMap memory
	closedContext->IDMap.map = NULL;
	for (int poolType = 0; poolType < OCT_typesTotal; poolType++) {
		free(closedContext->pools[poolType].array);
		closedContext->pools[poolType].array = NULL;
	}

	if (closedContextIndex != lastContextIndex) {															// swap replace to maintain a dense array
		iOCT_entityContext* closedContextMemory = closedContext;
		iOCT_entityContext* lastContextData = &game->entityContextPool[lastContextIndex];
		*closedContextMemory = *lastContextData;

		game->entityContextMap[lastContextID] = closedContextIndex;						// swap replace ID mapping and mark the old ID as free
	}
	game->entityContextCounter -= 1;
	game->entityContextMap[closedContextID] = iOCT_NO_ENTITYCONTEXT;
}

/// <summary>
/// Gets a generic pointer to any entity or component in an entityContext. Works as long as the ID is registered, regardless of the state of the entity or component.
/// </summary>
/// <param name="entityContextID"></param>
/// <param name="ID"></param>
/// <param name="type"></param>
/// <returns></returns>
void* iOCT_getByID(OCT_ID entityContextID, OCT_ID entityID, OCT_types type) {
	if (entityID == iOCT_NOPARENT) {
		return NULL;
	}

	iOCT_IDMap* map = iOCT_IDMap_get(entityContextID);
	OCT_index index = *iOCT_IDMap_access(entityContextID, entityID, type);

	iOCT_pool* pool = iOCT_pool_get(entityContextID, type);
	return (char*)pool->array + (index * pool->componentSize);
}

void OCT_entityContext_update(OCT_entityHandle root) {
	iOCT_entityContext_update(root.entityContextID);
}
void iOCT_entityContext_update(OCT_ID contextID) {
	iOCT_transform2D_propagate(contextID);
}



