#pragma once
#include "OCT_Math.h"
#include "cOCT_EngineStructure.h"
#include "OCT_Errors.h"
#include "ECS/types_internal.h"

#define iOCT_NO_COMPONENT OCT_GENERIC_NONE //unless you somehow end up with that many objects
#define iOCT_NOPARENT OCT_NULL_ID

#define iOCT_GAMEOBJECT_FAILED OCT_GENERIC_FAIL

#define iOCT_ENTITY_DEFAULT_MAX 1024

struct iOCT_entity{
	OCT_ID contextID;
	OCT_ID entityID;

	OCT_ID parentID;		// each entity can have at most one of each component type
	OCT_ID transformID;
	OCT_ID hitBoxID;	// if more hitboxes are needed, add more child objects
	///
	uint64_t componentsMask;	// tracks if the object has each component
};

extern OCT_handle testActiveEntity;

iOCT_entity* iOCT_entity_get(iOCT_entityContext* context, OCT_ID entityID);
OCT_ID iOCT_entity_new(iOCT_entityContext* context, OCT_ID parentID);
bool iOCT_entity_hasComponent(iOCT_entityContext* context, OCT_ID entityID, OCT_ECSTypes component);
void iOCT_entity_updateMask(iOCT_entityContext* context, OCT_ID entityID, OCT_ECSTypes componentType);
iOCT_entity* iOCT_entity_getParent(iOCT_entityContext* context, OCT_ID entityID);

