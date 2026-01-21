#pragma once
#include "ECS/entitySet/entitySet.h"
#include "standards/ECSStandards_internal.h"

#include "OCT_Math.h"

#define iOCT_ENTITYSET_DEFAULT_MAX 64
#define iOCT_POOLSIZE_DEFAULT 64

typedef iOCT_ID iOCT_entityContextID;
typedef iOCT_ID iOCT_entityID;

typedef struct iOCT_ECS {
	OCT_index* iOCT_entitySetMap;
	iOCT_entityContext* iOCT_entitySetPool;
	OCT_counter* iOCT_entitySetCounter;
} iOCT_ECS;

/// <summary>
/// entitySets define which pools interact with each other. Each holds a rootEntity, which is by default the first in the entity pool.
/// </summary>
typedef struct iOCT_entitySet{
	iOCT_entityContextID entitySetID;
	iOCT_entityID rootEntityID;

	iOCT_IDMap IDmap;
	iOCT_pool pools[OCT_componentsTotal];
} iOCT_entityContext;

/// <summary>
/// Pools manage the arrays of data. Each entitySet can have at most 1 pool per type. The arrays are contigous and allocated when a new pool is created. 
/// </summary>
typedef struct iOCT_pool {
	iOCT_entityContextID entitySetID;
	OCT_componentTypes componentType;

	OCT_counter counter;
	OCT_counter capacity;
	void* array;
} iOCT_pool;

/// <summary>
/// Maps hold lists of pool array locations, indexed by ID
/// </summary>
typedef struct iOCT_IDMap {
	iOCT_entityContextID entitySetID;
	size_t counter;
	size_t* array;
} iOCT_IDMap;

void iOCT_globalLists_initialize();

iOCT_entityContext* iOCT_entitySet_get(iOCT_entityContextID entitySetID);
OCT_entityHandle iOCT_entityContext_open();

iOCT_pool* iOCT_pool_get(iOCT_entityContextID entitySetID, OCT_componentTypes componentType);
bool iOCT_pool_full(iOCT_entityContext* entityCtx, OCT_componentTypes componentType);
OCT_counter* iOCT_counter_get(iOCT_entityContextID entitySetID, OCT_componentTypes componentType);

iOCT_ID iOCT_ID_new(iOCT_entityContext* entitySet, OCT_index index);