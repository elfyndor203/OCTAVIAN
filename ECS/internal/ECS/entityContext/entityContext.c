#include "entityContext_internal.h"
#include <string.h>
#include <stdlib.h>

#include "OCT_EngineStructure.h"
#include "ECS/ECS/ECSModule_internal.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/components/position2D/position2D_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"


iOCT_entityContext* iOCT_entityContext_get(OCT_ID entityContextID) {				// valid as long as the entitySet exists
	OCT_index index = iOCT_ECS_active->entityContextMap[entityContextID];
	return &iOCT_ECS_active->entityContextPool[index];
}

/// <summary>
/// Opens and initializes a new entityContext. Allocates pool and ID arrays, then returns the root entity handle for use. 
/// </summary>
OCT_entityHandle iOCT_entityContext_open() {
	iOCT_game_ECS* game = iOCT_ECS_active;
	OCT_ID entityContextID = (OCT_ID)game->entityContextCounter;	// Count will always be the next available slot
	game->entityContextCounter += 1;
	game->entityContextMap[entityContextID] = (OCT_index)entityContextID; // ID will start the same as the index
	OCT_index index = iOCT_entityContext_get(entityContextID);

	iOCT_entityContext* newEntityContext = &game->entityContextPool[index];	// get the next available slot in the entityContext pool

	newEntityContext->entityContextID = entityContextID;
	iOCT_IDMap_allocate(entityContextID);
	for (int poolType = 0; poolType < OCT_typesTotal; poolType++) {			// create and log each pool type
		iOCT_pool_allocate(&newEntityContext, poolType);
	}
	iOCT_entity_new(entityContextID, iOCT_NOPARENT);						// Create root entity

	printf("Created entityContext with ID %zu\n", entityContextID);
	OCT_entityHandle rootHandle = { entityContextID, newEntityContext->rootEntityID };
	return rootHandle;
}

/// <summary>
/// Frees all memory used by the entityContext. Handles bookkeeping by swap replacing with the last entityContext if necessary. 
/// </summary>
/// <param name="closedContextID"></param>
void iOCT_entityContext_close(OCT_ID closedContextID) {
	iOCT_game_ECS* game = iOCT_ECS_active;
	iOCT_entityContext* closedContext = iOCT_entityContext_get(closedContextID);
	OCT_index closedContextIndex = game->entityContextMap[closedContextID];
	OCT_index lastContextIndex = game->entityContextCounter - 1;									
	OCT_ID lastContextID = game->entityContextPool[lastContextIndex].entityContextID;

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
	game->entityContextMap[closedContextID] = iOCT_NO_ENTITYCONTEXT;
}

void* iOCT_getByID(OCT_ID entityContextID, OCT_ID ID, OCT_types componentType) {
	iOCT_IDMap* map = iOCT_IDMap_get(entityContextID);

	if (componentType != map->array[ID].componentType) {
		OCT_logError(EXIT_GENERIC_REPLACELATER);
		return NULL;
	}

	OCT_index index = map->array[ID].index;

	iOCT_pool* pool = iOCT_pool_get(entityContextID, componentType);
	return (char*)pool->array + (index * pool->componentSize);
}



