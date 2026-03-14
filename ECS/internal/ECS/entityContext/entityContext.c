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

static size_t sizeList[OCT_typesTotal] = {
	sizeof(iOCT_entity),
	sizeof(iOCT_transform2D),
	sizeof(iOCT_hitBox2D),
};

iOCT_entityContext* iOCT_entityContext_get(OCT_ID contextID) {				// valid as long as the entityContext exists
	OCT_index index = iOCT_ECS_instance.entityContextMap[contextID];
	return &iOCT_ECS_instance.entityContextPool[index];
}

OCT_pool* iOCT_pool_get(iOCT_entityContext* context, OCT_types componentType) {
	return &context->pools[componentType];
}

/// <summary>
/// Opens a new entity context in the current ECS instance. Allocates initial needed memory and returns the root handle for use.
/// </summary>
/// <returns></returns>
OCT_engineHandle OCT_entityContext_open() {
	return iOCT_entityContext_open();
}

OCT_engineHandle iOCT_entityContext_open() {
	OCT_ID entityContextID = (OCT_ID)iOCT_ECS_instance.entityContextCounter;	// Count will always be the next available slot
	iOCT_ECS_instance.entityContextCounter += 1;
	iOCT_ECS_instance.entityContextMap[entityContextID] = (OCT_index)entityContextID; // ID will start the same as the index
	// printf("Created entityContext with ID %" PRIu64 "\n", entityContextID);

	iOCT_entityContext* newContext = iOCT_entityContext_get(entityContextID);	// get the next available slot in the entityContext pool

	newContext->contextID = entityContextID;
	newContext->currentMaxDepth = -1;
	memset(&newContext->depthEnds, 0, sizeof(OCT_index) * iOCT_TRANSFORM_MAXDEPTH);
	newContext->IDMap = OCT_IDMap_init(entityContextID, iOCT_ENGINEPOOL_DEFAULTSIZE * OCT_typesTotal);
	for (int poolType = 0; poolType < OCT_typesTotal; poolType++) {			// create and log each pool type
		newContext->pools[poolType] = OCT_pool_init(newContext->contextID, iOCT_ENGINEPOOL_DEFAULTSIZE, sizeList[poolType]);
	}

	iOCT_entity_new(newContext, iOCT_NOPARENT);						// Create root entity
	OCT_engineHandle rootHandle = { entityContextID, iOCT_ROOT_ID };
	return rootHandle;
}

/// <summary>
/// Frees all memory used by the entityContext. Handles bookkeeping by swap replacing with the last entityContext if necessary. 
/// </summary>
/// <param name="closedContextID"></param>
void OCT_entityContext_close(OCT_engineHandle rootHandle) {
	iOCT_entityContext* context = iOCT_entityContext_get(rootHandle.contextID);
	iOCT_entityContext_close(context);
}
void iOCT_entityContext_close(iOCT_entityContext* closedContext) {
	iOCT_manager_ECS* game = &iOCT_ECS_instance;
	OCT_index closedContextIndex = game->entityContextMap[closedContext->contextID];
	OCT_index lastContextIndex = game->entityContextCounter - 1;									
	OCT_ID lastContextID = game->entityContextPool[lastContextIndex].contextID;

	free(closedContext->IDMap.array);												// Free pool and IDMap memory
	closedContext->IDMap.array = NULL;
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
	game->entityContextMap[closedContext->contextID] = iOCT_NO_ENTITYCONTEXT;
}

/// <summary>
/// Gets a generic pointer to any entity or component in an entityContext. Works as long as the ID is registered, regardless of the state of the entity or component.
/// </summary>
/// <param name="entityContextID"></param>
/// <param name="ID"></param>
/// <param name="type"></param>
/// <returns></returns>
void* iOCT_getByID(iOCT_entityContext* context, OCT_ID ID, OCT_types type) {
	if (ID == iOCT_NOPARENT) {
		return NULL;
	}

	OCT_IDMap* map = &context->IDMap;

	if (type != map->array[ID].type) {
		OCT_logError(EXIT_GENERIC_REPLACELATER);
		return NULL;
	}

	OCT_index index = map->array[ID].index;

	OCT_pool* pool = iOCT_pool_get(context, type);
	return (char*)pool->array + (index * pool->elementSize);
}

void OCT_entityContext_update(OCT_engineHandle root) {
	iOCT_entityContext* context = iOCT_entityContext_get(root.contextID);
	iOCT_entityContext_update(context);
}
void iOCT_entityContext_update(iOCT_entityContext* context) {
	iOCT_transform2D_propagate(context);
}



