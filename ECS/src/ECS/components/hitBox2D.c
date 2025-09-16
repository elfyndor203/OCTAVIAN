#include "ECS/gameObjects.h"

#include "ECS/components/hitBox2D.h"
#include "ECS/components/position2D.h"

vector2D defaultHitBox2D = { DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y };

size_t addNewHitBox2D(size_t parentIndex) {
	gameObject* parentObject = &gameObjectsPool[parentIndex];

	hitBox2D newHitBox2D = { 0 };
	newHitBox2D.poolIndex = hitBox2DCounter;
	newHitBox2D.parentIndex = parentIndex;

	parentObject->componentsMask |= (1ULL << componentHitBox2D);			// parent object knows it exists
	parentObject->positionIndex = newHitBox2D.poolIndex;

	resizeHitBox2D(newHitBox2D.poolIndex, DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y);

	hitBox2DPool[hitBox2DCounter] = newHitBox2D;
	hitBox2DCounter += 1;
	return newHitBox2D.poolIndex;
}

void resizeHitBox2D(size_t hitBoxIndex, size_t sizeX, size_t sizeY) {
	hitBox2D* hitBoxToInit = &hitBox2DPool[hitBoxIndex];
	gameObject* parentObject = &gameObjectsPool[hitBoxToInit->parentIndex];

	vector2D bottom = { sizeX, 0 };
	vector2D right = { 0, sizeY };
	vector2D top = { -sizeX, 0 };
	vector2D left = { 0, -sizeY };

	hitBoxToInit->bottom = bottom;
	hitBoxToInit->right = right;
	hitBoxToInit->top = top;
	hitBoxToInit->left = left;

	hitBoxToInit->origin = position2DPool[parentObject->positionIndex].globalPosition2D;
}

void generateHitBox2D(size_t hitBoxIndex, vector2D origin) {

}

//hitBox2D* createDefaultHitBox2D(gameObject* parent) {
//	hitBox2D* newHitBox2D = mallocCheck((sizeof(hitBox2D)), "newHitBox2D");
//
//	newHitBox2D->parent = parent;
//	newHitBox2D->origin = originZeroZero;
//	newHitBox2D->width = defaultHitBoxSize;
//	newHitBox2D->height = defaultHitBoxSize;
//
//	initializeHitBox2DVectors(&newHitBox2D);
//	return newHitBox2D;
//}
//
//void initializeHitBox2DVectors(hitBox2D* hitBox2DToSet) {
//	vector2D bottom = { hitBox2DToSet->width, 0 };
//	vector2D right = { 0, hitBox2DToSet->height };
//	vector2D top = { -hitBox2DToSet->width, 0 };
//	vector2D left = { 0, -hitBox2DToSet->height };
//
//	hitBox2DToSet->bottom = bottom;
//	hitBox2DToSet->right = right;
//	hitBox2DToSet->top = top;
//	hitBox2DToSet->left = left;
//}