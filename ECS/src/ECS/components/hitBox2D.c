#include "ECS/components/hitBox2D.h"

size_t addNewHitBox2D(size_t parentIndex) {
	hitBox2D newHitBox2D = { 0 };
	newHitBox2D.poolIndex = hitBox2DCounter;
	newHitBox2D.parentIndex = parentIndex;

	hitBox2DPool[hitBox2DCounter] = newHitBox2D;
	hitBox2DCounter += 1;
	return newHitBox2D.poolIndex;
}

void initializeHitBox2D(hitBox2D* hitBox) {

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