#pragma once
#include "ECS/entitySet/entitySet.h"
#include "standards/ECSStandards_internal.h"

#include "OCT_Math.h"

#define iOCT_ENTITYSET_DEFAULT_MAX 8
#define iOCT_POOLCOUNT_DEFAULT_MAX iOCT_ENTITYSET_DEFAULT_MAX * OCT_componentsTotal
#define iOCT_POOLSIZE_DEFAULT 64

typedef size_t iOCT_entitySetID;
typedef size_t iOCT_poolID;

/// <summary>
/// entitySets define which pools interact with each other. Each group of interactable entities and their components are managed by the same entitySet. 
/// </summary>
typedef struct iOCT_entitySet{
	iOCT_entitySetID entitySetID;
	iOCT_poolID pools[OCT_componentsTotal];

} iOCT_entitySet;

/// <summary>
/// Pools manage the contiguous arrays of information
/// </summary>
typedef struct iOCT_pool {
	iOCT_entitySetID entitySetID;
	iOCT_poolID poolID;
	OCT_componentTypes componentType;

	OCT_counter counter;
	void* pool;
} iOCT_pool;

extern iOCT_entitySet iOCT_entitySetList[iOCT_ENTITYSET_DEFAULT_MAX];
extern OCT_counter iOCT_entitySetCounter;
extern iOCT_pool iOCT_poolList[iOCT_POOLCOUNT_DEFAULT_MAX];
extern OCT_counter iOCT_poolCounter;

void iOCT_entitySetList_initialize();

iOCT_entitySet* iOCT_entitySet_get(iOCT_entitySetID entitySetID);
iOCT_entitySetID iOCT_entitySet_new();

iOCT_pool* iOCT_pool_get(iOCT_entitySetID entitySetID, OCT_componentTypes componentType);
OCT_counter* iOCT_counter_get(iOCT_entitySetID entitySetID, OCT_componentTypes componentType);

