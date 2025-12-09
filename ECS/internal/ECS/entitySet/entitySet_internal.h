#pragma once
#include "ECS/entitySet/entitySet.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/entity/entity_internal.h"
#include "ECS/components/position2D/position2D_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"

typedef size_t iOCT_entitySetID;

/// For each group of interactable objects, there is an OCT_entitySet that contains pools of each entity and each component type in it, along with counters
/// For these pools, the data is stored directly
/// A scene is tied to its root object. To make a child of the root, use OCT_ROOT_OBJECT
/// For the pool of entitySets, pointers are stored
typedef struct iOCT_entitySet{
	iOCT_entitySetID entitySetID;
	iOCT_entity rootObject;

	OCT_counter entityCounter;
	iOCT_entity entityPool[iOCT_ENTITY_DEFAULT_MAX];

	OCT_counter position2DCounter;
	iOCT_position2D position2DPool[iOCT_ENTITY_DEFAULT_MAX];
	OCT_counter transform2DCounter;
	iOCT_transform2D transform2DPool[iOCT_ENTITY_DEFAULT_MAX];
	OCT_counter hitBox2DCounter;
	iOCT_hitBox2D hitBox2DPool[iOCT_ENTITY_DEFAULT_MAX];
} iOCT_entitySet;

iOCT_entitySet* iOCT_entitySetPool[_OCT_ENTITYSET_DEFAULT_MAX]; /// pointers

iOCT_entitySet* iOCT_entitySet_get(iOCT_entitySetID entitySetID);
iOCT_entitySetID iOCT_entitySet_new();
void iOCT_entitySet_initialize();

