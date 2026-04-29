#pragma once
#include "OCT_Math.h"
#include "cOCT_EngineStructure.h"
#include "OCT_Errors.h"
#include "ECS/types_internal.h"

struct iOCT_entity{
	OCT_ID contextID;
	OCT_ID entityID;

	OCT_ID parentID;		// each entity can have at most one of each component type
	OCT_ID transformID;
	OCT_ID physicsID;
	OCT_ID colliderID;
	OCT_ID hitBoxID;
	OCT_ID spriteID;
	OCT_ID cameraID;
	///
	uint64_t componentsMask;	// tracks if the object has each component
};

iOCT_entity* iOCT_entity_get(iOCT_entityContext* context, OCT_ID entityID);
OCT_ID iOCT_entity_getCompID(iOCT_entityContext* context, OCT_ID entityID, OCT_ECSTypes componentType);

OCT_ID iOCT_entity_new(iOCT_entityContext* context, OCT_ID parentID);
void iOCT_entity_delete(iOCT_entityContext* context, OCT_ID entityID);

bool iOCT_entity_hasComponent(iOCT_entityContext* context, OCT_ID entityID, OCT_ECSTypes component);
void iOCT_entity_updateMask(iOCT_entityContext* context, OCT_ID entityID, OCT_ECSTypes componentType);
iOCT_entity* iOCT_entity_getParent(iOCT_entityContext* context, OCT_ID entityID);

