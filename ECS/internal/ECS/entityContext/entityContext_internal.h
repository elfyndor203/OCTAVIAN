#pragma once
#include "ECS/entitySet/entitySet.h"
#include "pools_internal.h"
#include "IDMap_internal.h"

#include "standards/ECSStandards_internal.h"
#include "OCT_Math.h"

#define iOCT_ENTITYCONTEXT_DEFAULT_MAX 64

/// <summary>
/// Opening an entityContext allows you to create entities that interact with each other. Each context manages its own pools and IDmap.
/// </summary>
typedef struct entityContext{
	iOCT_ID entityContextID;
	iOCT_ID rootEntityID;

	iOCT_IDMap IDmap;
	iOCT_pool pools[OCT_componentsTotal];
} iOCT_entityContext;

iOCT_entityContext* iOCT_entityContext_get(iOCT_ID entityContextID);
OCT_entityHandle iOCT_entityContext_open();
void iOCT_entityContext_close();
void* iOCT_getByID(iOCT_ID entityContextID, OCT_componentTypes componentType, iOCT_ID ID);

