#pragma once
#include "ECS/gameObject/gameObject.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"

#define OCT_MAX_GAMEOBJECT 1024
#define OCT_NO_COMPONENT SIZE_MAX //unless you somehow end up with that many objects

typedef struct iOCT_gameObject{
	OCT_gameObjectID poolIndex;

	bool is3D;					// in case of the rare 3d position usage
	OCT_gameObjectID parentIndex;		// single index in pools of components it can physically only have one of

	OCT_componentID positionIndex;		
	OCT_componentID transformIndex;

	/// optional
	OCT_componentID hitBoxIndex;
	///
	uint64_t componentsMask;	// tracks if the object has each component
} iOCT_gameObject;

OCT_gameObjectID gameObject_createNew(OCT_gameObjectID parentIndex, bool is3D);
bool gameObject_hasComponent(OCT_gameObjectID iOCT_gameObject, componentTypes component);

iOCT_gameObject gameObject_generateRoot();
