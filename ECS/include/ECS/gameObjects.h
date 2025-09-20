#pragma once

#define MAX_GAMEOBJECTS 1024

#include "myStandards.h"
#include "ECS/componentTypes.h"

typedef struct gameObject{
	size_t poolIndex;

	bool is3D;					// in case of the rare 3d position usage
	size_t parentIndex;		// single index in pools of components it can physically only have one of

	size_t positionIndex;		
	size_t transformIndex;
	size_t hitBoxIndex;
	
	uint64_t componentsMask;	// tracks if the object has each component
} gameObject;

gameObject createGameObject(size_t parentIndex, bool is3D);
