#pragma once
#include "standards/ECSStandards_internal.h"

#include "OCT_Math.h"

#define iOCT_NO_COMPONENT OCT_GENERIC_NONE //unless you somehow end up with that many objects
#define iOCT_GAMEOBJECT_FAILED OCT_GENERIC_FAIL

#define iOCT_ENTITY_DEFAULT_MAX 1024

typedef struct iOCT_entity{
	iOCT_ID entitySetID;
	iOCT_ID entityID;

	bool is3D;					// in case of the rare 3d position usage

	iOCT_ID parentID;		// each entity can have at most one of each component type
	iOCT_ID positionID;
	iOCT_ID transformID;
	iOCT_ID hitBoxID;	// if more hitboxes are needed, add more child objects
	///
	uint64_t componentsMask;	// tracks if the object has each component
} iOCT_entity;

extern OCT_entityHandle testActiveEntity;

iOCT_ID iOCT_entity_new(iOCT_entityContextID entitySetID, iOCT_entityID parentID);
bool iOCT_entity_hasComponent(iOCT_entityContextID entitySetID, iOCT_entityID entityID, OCT_componentTypes component);

