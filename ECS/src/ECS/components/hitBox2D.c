#include "ECS/gameObjects.h"

#include "ECS/components/hitBox2D.h"
#include "ECS/components/position2D.h"

vector2D defaultHitBox2D = { DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y };

size_t hitBox2DAddNew(size_t parentIndex) {
	gameObject* parentObject = &gameObjectsPool[parentIndex];

	hitBox2D newHitBox2D = { 0 };
	newHitBox2D.poolIndex = hitBox2DCounter;
	newHitBox2D.parentIndex = parentIndex;

	parentObject->componentsMask |= (1ULL << componentHitBox2D);			// parent object knows it exists
	parentObject->positionIndex = newHitBox2D.poolIndex;

	hitBox2DResize(newHitBox2D.poolIndex, DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y);

	hitBox2DPool[hitBox2DCounter] = newHitBox2D;
	hitBox2DCounter += 1;
	return newHitBox2D.poolIndex;
}

void hitBox2DResize(size_t hitBoxIndex, size_t sizeX, size_t sizeY) {
	hitBox2D* hitBoxToInit = &hitBox2DPool[hitBoxIndex];
	gameObject* parentObject = &gameObjectsPool[hitBoxToInit->parentIndex];
	vector2D* bottomLeft = &hitBoxToInit->bottomLeft;

	bottomLeft->x = -sizeX / 2;
	bottomLeft->y = -sizeY / 2;
}

hitBoxVertices hitBox2DGenerateVertices(size_t hitBoxIndex) {
	hitBox2D* hitBoxToInit = &hitBox2DPool[hitBoxIndex];
	
	hitBoxVertices newHitBoxVertices = { 0 };
	newHitBoxVertices.poolIndex = hitBox2DCounter;
}

