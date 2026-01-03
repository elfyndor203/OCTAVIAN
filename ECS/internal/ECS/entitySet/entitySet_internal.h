#pragma once
#include "ECS/entitySet/entitySet.h"
#include "standards/ECSStandards_internal.h"

#include "OCT_Math.h"

#define iOCT_ENTITYSET_DEFAULT_MAX 64
#define iOCT_POOLSIZE_DEFAULT 64
#define iOCT_ROOT_DEFAULT 0

typedef size_t iOCT_entitySetID;
typedef size_t iOCT_poolID;

/// <summary>
/// entitySets define which pools interact with each other. Each holds a rootEntity, which is by default the first in the entity pool.
/// </summary>
typedef struct iOCT_entitySet{
	iOCT_entitySetID entitySetID;
	iOCT_entityID rootEntityID;
	iOCT_poolID pools[OCT_componentsTotal];

} iOCT_entitySet;

/// <summary>
/// Pools manage the arrays of data. Each entitySet can have at most 1 pool per type. The arrays are contigous and allocated when a new pool is created. 
/// </summary>
typedef struct iOCT_pool {
	iOCT_entitySetID entitySetID;
	iOCT_poolID poolID;
	OCT_componentTypes componentType;

	OCT_counter counter;
	void* array;
} iOCT_pool;

extern iOCT_entitySet iOCT_entitySetList[iOCT_ENTITYSET_DEFAULT_MAX];
extern OCT_counter iOCT_entitySetCounter;
extern iOCT_pool iOCT_poolList[iOCT_ENTITYSET_DEFAULT_MAX * OCT_componentsTotal];
extern OCT_counter iOCT_poolCounter;

void iOCT_globalLists_initialize();

iOCT_entitySet* iOCT_entitySet_get(iOCT_entitySetID entitySetID);
OCT_entityHandle iOCT_entitySet_new();

iOCT_pool* iOCT_pool_get(iOCT_entitySetID entitySetID, OCT_componentTypes componentType);
OCT_counter* iOCT_counter_get(iOCT_entitySetID entitySetID, OCT_componentTypes componentType);

