#pragma once
#include <stdarg.h>
#include <string.h>

#include "componentTypes.h"
#include "position2D.h"
#include "transform2D.h"
#include "hitBox2D.h"

typedef struct gameObject{										// each gameObject takes an array of components
	void* componentsList[componentsTotal];
	int componentsCountTotal;
	uint64_t componentsMask;							// tracks if the object has that component
	uint16_t componentsCountPer[componentsTotal];		// tracks the number of each component
} gameObject;


void printComponentsList(gameObject* parent);

gameObject* createBlankGameObject();

void addComponent(gameObject* parentObject, componentTypes componentType, void* componentToAdd);

gameObject* createGameObject(int componentsToAdd, ...);
