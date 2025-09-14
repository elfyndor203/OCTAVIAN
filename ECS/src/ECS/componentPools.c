#include "ECS/componentPools.h"

size_t addNewPosition2D(size_t parentIndex) {
	position2D newPosition2D = { 0 };
	newPosition2D.poolIndex = position2DCounter;
	newPosition2D.parentIndex = parentIndex;

	position2DPool[position2DCounter] = newPosition2D;
	position2DCounter += 1;											
	return newPosition2D.poolIndex;						
}

size_t addNewTransform2D(size_t parentIndex) {
	transform2D newtransform2D = { 0 };
	newtransform2D.poolIndex = transform2DCounter;
	newtransform2D.parentIndex = parentIndex;

	transform2DPool[transform2DCounter] = newtransform2D;
	transform2DCounter += 1;
	return newtransform2D.poolIndex;
}

size_t addNewHitBox2D(size_t parentIndex) {
	hitBox2D newHitBox2D = { 0 };
	newHitBox2D.poolIndex = hitBox2DCounter;
	newHitBox2D.parentIndex = parentIndex;

	hitBox2DPool[hitBox2DCounter] = newHitBox2D;
	hitBox2DCounter += 1;
	return newHitBox2D.poolIndex;
}

void initializeAllPools() {
	size_t maxComponentsPerType = INITIAL_MAX_COMPONENTS_PER_TYPE;

	position2DCounter = 0;
	transform2DCounter = 0;
	hitBox2DCounter = 0;
}

