#pragma once
#include "ECS/entitySet/entitySet.h"
#include "pools_internal.h"
#include "IDMap_internal.h"

#include "standards/ECSStandards_internal.h"
#include "OCT_Math.h"

#define iOCT_ENTITYCONTEXT_DEFAULT_MAX 64


/// <summary>
/// entitySets define which pools interact with each other. Each holds a rootEntity, which is by default the first in the entity pool.
/// </summary>
typedef struct entityContext{
	iOCT_ID entityContextID;
	iOCT_ID rootEntityID;

	iOCT_IDMap IDmap;
	iOCT_pool pools[OCT_componentsTotal];
} iOCT_entityContext;

void iOCT_globalLists_initialize();

iOCT_entityContext* iOCT_entityContext_get(iOCT_ID entityContextID);
OCT_entityHandle iOCT_entityContext_open();

