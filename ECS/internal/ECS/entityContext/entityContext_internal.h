#pragma once
#include "pools_internal.h"
#include "IDMap_internal.h"

#include "OCT_Math.h"
#include "OCT_EngineStructure.h"
#include "OCT_Errors.h"

#define iOCT_ENTITYCONTEXT_DEFAULT_MAX 64
#define iOCT_ROOT_ID 0
#define iOCT_NO_ENTITYCONTEXT OCT_GENERIC_NONE

/// <summary>
/// Opening an entityContext allows you to create entities that interact with each other. Each context manages its own pools and IDmap.
/// </summary>
typedef struct entityContext{
	OCT_ID entityContextID;
	OCT_ID rootEntityID;

	iOCT_IDMap IDMap;
	iOCT_pool pools[OCT_typesTotal];
} iOCT_entityContext;

iOCT_entityContext* iOCT_entityContext_get(OCT_ID entityContextID);
OCT_entityHandle iOCT_entityContext_open();
void iOCT_entityContext_close(OCT_ID closedContextID);
void* iOCT_getByID(OCT_ID entityContextID, OCT_ID ID, OCT_types componentType);

