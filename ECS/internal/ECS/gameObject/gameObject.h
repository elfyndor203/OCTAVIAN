#pragma once

#define MAX_gameObject 1024

#include "standards/myStandards.h"
#include "ECS/components/componentTypes/componentTypes.h"

typedef struct gameObject{
	gameObjectIndex poolIndex;

	bool is3D;					// in case of the rare 3d position usage
	gameObjectIndex parentIndex;		// single index in pools of components it can physically only have one of

	componentIndex positionIndex;		
	componentIndex transformIndex;
	componentIndex hitBoxIndex;
	
	uint64_t componentsMask;	// tracks if the object has each component
} gameObject;

gameObjectIndex gameObjectCreateNew(gameObjectIndex parentIndex, bool is3D);
bool gameObjectHasComponent(gameObjectIndex gameObject, componentTypes component);
