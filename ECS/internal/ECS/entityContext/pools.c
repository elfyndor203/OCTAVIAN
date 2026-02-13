#include "pools_internal.h"
#include "entityContext_internal.h"

#include "ECS/entityContext/IDMap_internal.h"
#include "ECS/entity/entity_internal.h"
#include "ECS/components/position2D/position2D_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"

static size_t iOCT_componentSizeList[OCT_componentsTotal] = { sizeof(iOCT_entity), sizeof(iOCT_transform2D), sizeof(iOCT_hitBox2D) };	//NOTE __MUST__ MATCH COMPONENTTYPES
//static iOCT_pool failedPool = { OCT_GENERIC_FAIL, OCT_GENERIC_FAIL, NULL };

iOCT_pool* iOCT_pool_get(iOCT_ID entityContextID, OCT_componentTypes componentType) {
	iOCT_entityContext* entityContext = iOCT_entityContext_get(entityContextID);
	return &entityContext->pools[componentType];
}

/// <summary>
/// Allocates memory for a single entityContext. Allows creation of all pools without rewriting when new component types are added
/// </summary>
bool iOCT_pool_allocate(iOCT_ID entityContextID, OCT_componentTypes componentType) {
	iOCT_entityContext* entityContext = iOCT_entityContext_get(entityContextID);
	iOCT_pool* pool = &entityContext->pools[componentType];		// locate pool

	pool->entityContextID = entityContextID;					// set default values
	pool->componentType = componentType;
	pool->counter = 0;
	pool->capacity = iOCT_POOLSIZE_DEFAULT;
	pool->componentSize = iOCT_componentSizeList[componentType];
	pool->array = calloc(iOCT_POOLSIZE_DEFAULT, iOCT_componentSizeList[componentType]);
	if (!pool->array) {
		return false;
	}
	return true;
}