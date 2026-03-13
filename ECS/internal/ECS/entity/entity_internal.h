#pragma once
#include "OCT_Math.h"
#include "OCT_EngineStructure.h"
#include "OCT_Errors.h"

#define iOCT_NO_COMPONENT OCT_GENERIC_NONE //unless you somehow end up with that many objects
#define iOCT_NOPARENT OCT_GENERIC_NONE

#define iOCT_GAMEOBJECT_FAILED OCT_GENERIC_FAIL

typedef struct iOCT_entity{
	OCT_ID entityContextID;
	OCT_ID entityID;

	OCT_ID parentID;		// each entity can have at most one of each component type
	OCT_ID transformID;
	OCT_ID hitBoxID;	// if more hitboxes are needed, add more child objects
	///
	uint64_t componentsMask;	// tracks if the object has each component
} iOCT_entity;

extern OCT_entityHandle testActiveEntity;

iOCT_entity* iOCT_entity_get(OCT_ID contextID, OCT_ID entityID);
OCT_ID iOCT_entity_new(OCT_ID contextID, OCT_ID parentID);
bool iOCT_entity_hasComponent(OCT_ID contextID, OCT_ID entityID, OCT_types component);
void iOCT_entity_updateMask(OCT_ID contextID, OCT_ID entityID, OCT_types componentType);
iOCT_entity* iOCT_entity_getParent(OCT_ID contextID, OCT_ID entityID);

