#include "entityContext_internal.h"

#include "OCT_EngineStructure.h"
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#include "ECS/module/ECSModule_internal.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"

static size_t sizeList[OCT_ECSTypes_total] = {
	sizeof(iOCT_entity),
	sizeof(iOCT_transform2D),
	sizeof(iOCT_hitBox2D),
};

iOCT_entityContext* iOCT_entityContext_get(OCT_ID contextID) {				// valid as long as the entityContext exists
	OCT_index index = OCT_IDMap_getIndex(&iOCT_ECS_instance.IDMap, contextID);
	return (iOCT_entityContext*)OCT_pool_access(&iOCT_ECS_instance.pool, index);
}

OCT_pool* iOCT_pool_get(iOCT_entityContext* context, OCT_ECSTypes componentType) {
	return &context->pools[componentType];
}

/// <summary>
/// Opens a new entity context in the current ECS instance.
/// </summary>
/// <returns></returns>
OCT_handle OCT_entityContext_open(OCT_handle* outRoot) {
	OCT_handle contextHandle = {
		.subsystem = OCT_subsystem_ECS,
		.containerID = OCT_subsystem_ECS,
		.objectID = iOCT_entityContext_open(),
		.type = OCT_handle_entityContext
	};
	OCT_handle root = {
		.subsystem = OCT_subsystem_ECS,
		.containerID = contextHandle.objectID,
		.objectID = iOCT_ROOT_ID,
		.type = OCT_handle_entity
	};
	*outRoot = root;
	return contextHandle;
}
OCT_ID iOCT_entityContext_open() {
	OCT_index newIndex;
	OCT_ID newID;
	iOCT_entityContext* newContext;

	newContext = (iOCT_entityContext*)OCT_pool_addTo(&iOCT_ECS_instance.pool, &newIndex);
	newID = OCT_IDMap_register(&iOCT_ECS_instance.IDMap, newIndex);

	newContext->contextID = newID;
	newContext->currentMaxDepth = -1; // prepare for root
	memset(&newContext->depthEnds, 0, sizeof(OCT_index) * iOCT_TRANSFORM_MAXDEPTH);

	newContext->IDMap = OCT_IDMap_init(OCT_subsystem_ECS, OCT_POOLSIZE_DEFAULT * OCT_ECSTypes_total);	// enough for all pools
	for (int poolType = 0; poolType < OCT_ECSTypes_total; poolType++) {
		newContext->pools[poolType] = OCT_pool_init(newContext->contextID, OCT_POOLSIZE_DEFAULT, sizeList[poolType]);
	}

	iOCT_entity_new(newContext, iOCT_NOPARENT);						// Create root entity
	return newID;
}

/// <summary>
/// Frees all memory used by the entityContext. Handles bookkeeping by swap replacing with the last entityContext if necessary. 
/// </summary>
/// <param name="closedContextID"></param>
void OCT_entityContext_close(OCT_handle contextHandle) {
	assert(contextHandle.type == OCT_handle_entityContext);

	iOCT_entityContext* context = iOCT_entityContext_get(contextHandle.objectID);
	iOCT_entityContext_close(context);
}
void iOCT_entityContext_close(iOCT_entityContext* closedContext) {
	OCT_index closedIndex = OCT_IDMap_deregister(&iOCT_ECS_instance.IDMap, closedContext->contextID);

	OCT_IDMap_free(&closedContext->IDMap);
	OCT_pool* pool;
	for (int poolType = 0; poolType < OCT_ECSTypes_total; poolType++) {
		pool = &closedContext->pools[poolType];
		OCT_pool_free(pool);
	}
	
	OCT_pool_delete(&iOCT_ECS_instance.pool, closedIndex, true);
}

/// <summary>
/// Gets a generic pointer to any entity or component in an entityContext. Works as long as the ID is registered, regardless of the state of the entity or component.
/// </summary>
/// <param name="entityContextID"></param>
/// <param name="ID"></param>
/// <param name="type"></param>
/// <returns></returns>
void* iOCT_getByID(iOCT_entityContext* context, OCT_ID ID, OCT_ECSTypes type) {
	if (ID == iOCT_NOPARENT) {
		return NULL;
	}

	OCT_IDMap* map = &context->IDMap;

	OCT_index index = OCT_IDMap_getIndex(map, ID);
	OCT_pool* pool = iOCT_pool_get(context, type);

	return OCT_pool_access(pool, index);
}

void OCT_entityContext_update(OCT_handle contextHandle) {
	assert(contextHandle.type == OCT_handle_entityContext);

	iOCT_entityContext* context = iOCT_entityContext_get(contextHandle.objectID);
	iOCT_entityContext_update(context);
}
void iOCT_entityContext_update(iOCT_entityContext* context) {
	iOCT_transform2D_propagate(context);
}



