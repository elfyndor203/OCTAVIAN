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
	OCT_index index = OCT_IDMap_getIndex(&iOCT_ECS_instance.IDMap, contextID);
	return (iOCT_entityContext*)OCT_pool_access(&iOCT_ECS_instance.contextPool, index);
}

OCT_pool* iOCT_pool_get(iOCT_entityContext* context, OCT_types componentType) {
	return &context->pools[componentType];
}

/// <summary>
/// Opens a new entity context in the current ECS instance. Allocates initial needed memory and returns the root handle for use.
/// </summary>
/// <returns></returns>
OCT_handle OCT_entityContext_open() {
	return iOCT_entityContext_open();
}

OCT_handle iOCT_entityContext_open() {
	OCT_index newIndex;
	OCT_ID newID;
	iOCT_entityContext* newContext;

	newContext = OCT_pool_add(&iOCT_ECS_instance.contextPool, &newIndex);
	newID = OCT_IDMap_register(&iOCT_ECS_instance.IDMap, 0, newIndex); // 0: type does not matter

	newContext->contextID = newID;
	newContext->currentMaxDepth = -1; // prepare for root
	memset(&newContext->depthEnds, 0, sizeof(OCT_index) * iOCT_TRANSFORM_MAXDEPTH);

	newContext->IDMap = OCT_IDMap_init(OCT_IDMAPTYPE_CONTAINER, OCT_POOLSIZE_DEFAULT * OCT_typesTotal);	// enough for all pools
	for (int poolType = 0; poolType < OCT_typesTotal; poolType++) {
		newContext->pools[poolType] = OCT_pool_init(newContext->contextID, OCT_POOLSIZE_DEFAULT, sizeList[poolType]);
	}

	iOCT_entity_new(newContext, iOCT_NOPARENT);						// Create root entity
	OCT_handle rootHandle = { newID, iOCT_ROOT_ID };
	return rootHandle;
}

/// <summary>
/// Frees all memory used by the entityContext. Handles bookkeeping by swap replacing with the last entityContext if necessary. 
/// </summary>
/// <param name="closedContextID"></param>
void OCT_entityContext_close(OCT_handle rootHandle) {
	iOCT_entityContext* context = iOCT_entityContext_get(rootHandle.ownerID);
	iOCT_entityContext_close(context);
}
void iOCT_entityContext_close(iOCT_entityContext* closedContext) {
	
	OCT_index closedIndex = OCT_IDMap_deregister(&iOCT_ECS_instance.IDMap, closedContext->contextID);

	free(closedContext->IDMap.array);												// Free pool and IDMap memory
	OCT_pool* pool;
	for (int poolType = 0; poolType < OCT_typesTotal; poolType++) {
		pool = &closedContext->pools[poolType];
		OCT_pool_free(pool);
	}
	
	OCT_pool_delete(&iOCT_ECS_instance.contextPool, closedIndex, true);
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

	OCT_index index = OCT_IDMap_getIndex(map, ID);
	OCT_pool* pool = iOCT_pool_get(context, type);

	return OCT_pool_access(pool, index);
}

void OCT_entityContext_update(OCT_handle root) {
	iOCT_entityContext* context = iOCT_entityContext_get(root.ownerID);
	iOCT_entityContext_update(context);
}
void iOCT_entityContext_update(iOCT_entityContext* context) {
	iOCT_transform2D_propagate(context);
}



