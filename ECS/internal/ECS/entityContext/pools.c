#include "pools_internal.h"
#include "entityContext_internal.h"
#include <stdlib.h>

#include "ECS/entityContext/registry_internal.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"

#include <assert.h>

static size_t iOCT_componentSizeList[OCT_typesTotal] = { sizeof(iOCT_entity), sizeof(iOCT_transform2D), sizeof(iOCT_hitBox2D)};	//NOTE __MUST__ MATCH COMPONENTTYPES

iOCT_pool* iOCT_pool_get(OCT_ID entityContextID, OCT_types componentType) {
	iOCT_entityContext* entityContext = iOCT_entityContext_get(entityContextID);
	return &entityContext->pools[componentType];
}

/// <summary>
/// Unsafe. Returns a pointer to any pool entry given its index.
/// </summary>
/// <param name="contextID"></param>
/// <param name="componentType"></param>
/// <returns></returns>
void* iOCT_pool_accessU(iOCT_pool* pool, OCT_index index) {
	return (char*)(pool->data) + (index * pool->stride);
}

/// <summary>
/// Allocates memory for a single entityContext. Allows creation of all pools without rewriting when new component types are added
/// </summary>
bool iOCT_pool_allocate(OCT_ID entityContextID, OCT_types componentType) {
	iOCT_entityContext* entityContext = iOCT_entityContext_get(entityContextID);
	iOCT_pool* pool = &entityContext->pools[componentType];		// locate pool

	pool->entityContextID = entityContextID;					// set default values
	pool->componentType = componentType;
	pool->count = 0;
	pool->capacity = iOCT_POOLSIZE_DEFAULT;
	pool->stride = iOCT_componentSizeList[componentType];
	pool->data = calloc(iOCT_POOLSIZE_DEFAULT, iOCT_componentSizeList[componentType]);
	if (!pool->data) {
		return false;
	}
	return true;
}

/// <summary>
/// Called when a pool entry needs to be added. Increments the counter and returns a pointer to the array slot and its index.
/// </summary>
/// <param name="contextID"></param>
/// <param name="componentType"></param>
/// <returns></returns>
void* iOCT_pool_push(OCT_ID contextID, OCT_types componentType, OCT_index* index) {
	iOCT_pool* pool = iOCT_pool_get(contextID, componentType);
	assert(pool->count < pool->capacity);

	return iOCT_pool_accessU(pool, componentType, pool->count++);
}