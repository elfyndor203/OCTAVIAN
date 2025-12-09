#pragma once
#include "standards/ECSStandards_internal.h"

#include "OCT_Math.h"
#include "ECS/components/componentTypes/componentTypes_internal.h"

#define iOCT_NO_COMPONENT GENERIC_FAIL //unless you somehow end up with that many objects
#define iOCT_GAMEOBJECT_FAILED GENERIC_FAIL

#define iOCT_ENTITY_DEFAULT_MAX 1024

typedef size_t iOCT_entitySetID;	// redeclare to ensure everything else knows this ID
typedef size_t iOCT_entityID;

typedef struct iOCT_entity{
	iOCT_entitySetID entitySetID;
	iOCT_entityID entityID;

	bool is3D;					// in case of the rare 3d position usage

	iOCT_entityID parentID;		// each entity can have at most one of each component type
	iOCT_componentID positionID;		
	iOCT_componentID transformID;
	iOCT_componentID hitBoxID;	// if more hitboxes are needed, add more child objects
	///
	uint64_t componentsMask;	// tracks if the object has each component
} iOCT_entity;

extern OCT_entityHandle testActiveEntity;

iOCT_entity* iOCT_entity_get(iOCT_entitySetID entitySetID, iOCT_entityID entityID);
iOCT_entity* iOCT_entity_getPool(iOCT_entitySetID entitySetID);
OCT_counter*  iOCT_entity_getCounter(iOCT_entitySetID entitySetID);

iOCT_entityID iOCT_entity_createNew(iOCT_entitySetID entitySetID, iOCT_entityID parentID);
bool iOCT_entity_hasComponent(iOCT_entitySetID entitySetID, iOCT_entityID entityID, OCT_componentTypes component);