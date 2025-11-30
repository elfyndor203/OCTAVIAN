#pragma once
#include "ECS/gameObject/gameObject.h"
#include "standards/ECSStandards_internal.h"
#include "ECS/components/componentTypes/componentTypes_internal.h"

#define iOCT_DEFAULT_MAX_GAMEOBJECTS 1024

#define iOCT_NO_COMPONENT GENERIC_FAIL //unless you somehow end up with that many objects
#define iOCT_GAMEOBJECT_FAILED GENERIC_FAIL

extern size_t iOCT_MAX_GAMEOBJECTS;

typedef struct iOCT_gameObject{
	iOCT_sceneID sceneID;
	iOCT_gameObjectID gameObjectID;
	iOCT_gameObjectID parentID;		// single index in pools of components it can physically only have one of

	bool is3D;					// in case of the rare 3d position usage

	OCT_componentID positionID;		
	OCT_componentID transformID;

	/// optional
	OCT_componentID hitBoxID;	// if more hitboxes are needed, add more child objects
	///
	uint64_t componentsMask;	// tracks if the object has each component
} iOCT_gameObject;

iOCT_gameObject* iOCT_gameObject_get(iOCT_sceneID sceneID, iOCT_gameObjectID gameObjectID);
iOCT_gameObject* iOCT_gameObject_getPool(iOCT_sceneID sceneID);
iOCT_counter* iOCT_gameObject_getCounter(iOCT_sceneID sceneID);

iOCT_gameObjectID iOCT_gameObject_createNew(iOCT_sceneID sceneID, iOCT_gameObjectID parentID);
bool iOCT_gameObject_hasComponent(iOCT_sceneID sceneID, iOCT_gameObjectID gameObjectID, OCT_componentTypes component);