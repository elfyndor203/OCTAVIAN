#pragma once
#include "standards/myStandards.h"

#include "ECS/components/componentTypes/componentTypes.h"

#define MAX_gameObject 1024

typedef struct gameObject{
	gameObjectIndex poolIndex;

	bool is3D;					// in case of the rare 3d position usage
	gameObjectIndex parentIndex;		// single index in pools of components it can physically only have one of

	componentIndex positionIndex;		
	componentIndex transformIndex;
	componentIndex hitBoxIndex;
	
	uint64_t componentsMask;	// tracks if the object has each component
} gameObject;

gameObjectIndex gameObject_createNew(gameObjectIndex parentIndex, bool is3D);
bool gameObject_hasComponent(gameObjectIndex gameObject, componentTypes component);
