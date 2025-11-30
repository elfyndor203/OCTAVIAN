#include "hitBox2D_internal.h"

#include "ECS/gameObject/gameObject_internal.h"
#include "ECS/scene/scene_internal.h"

#include "ECS/components/hitBox2D/hitBox2DVertices_internal.h"

OCT_componentID hitBox2D_addNew(OCT_gameObjectID parentIndex) {
	gameObject* parentObject = gameObject_get(parentIndex);

	hitBox2D newHitBox2D = { 0 };											// create blank object
	hitBox2D_getPool()[*hitBox2D_getCounter()] = newHitBox2D;					// copy into pool

	newHitBox2D.poolIndex = *hitBox2D_getCounter();							// can find itself
	newHitBox2D.parentIndex = parentIndex;									// can find its parent
	parentObject->componentsMask |= (1ULL << componentHitBox2D);			// parent object knows it exists
	parentObject->hitBoxIndex = newHitBox2D.poolIndex;						// parent can find it

	hitBox2D_resize(newHitBox2D.poolIndex, DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y);

	*hitBox2D_getCounter() += 1;												// update counter LAST
	printf("Added new hitBox2D to object %zu \n", parentIndex);
	return newHitBox2D.poolIndex;
}

void hitBox2D_resize(OCT_gameObjectID parentIndex, float sizeX, float sizeY) {
	hitBox2D_get(parentIndex)->size.x = sizeX;
	hitBox2D_get(parentIndex)->size.y = sizeY;

	hitBox2D_generateVertices(parentIndex);
}

/// API

OCT_componentID OCT_hitBox2D_addNew(OCT_gameObjectID parentIndex) {
	return hitBox2D_addNew(parentIndex);
}

void OCT_hitBox2D_resize(OCT_gameObjectID parentIndex, float sizeX, float sizeY) {
	hitBox2D_resize(parentIndex, sizeX, sizeY);
}