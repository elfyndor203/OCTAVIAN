#include "hitBox2D_internal.h"

#include "ECS/gameObject/gameObject_internal.h"
#include "ECS/scene/scene_internal.h"


vector2D defaultHitBox2D = { DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y };

componentIndex hitBox2D_addNew(gameObjectIndex parentIndex) {
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

void hitBox2D_resize(gameObjectIndex parentIndex, float sizeX, float sizeY) {
	hitBox2D_get(parentIndex)->size.x = sizeX;
	hitBox2D_get(parentIndex)->size.y = sizeY;

	hitBox2D_generateVertices(parentIndex);
}

subcomponentIndex hitBox2D_generateVertices(gameObjectIndex parentIndex) {
	hitBox2D* hitBox = hitBox2D_get(parentIndex);
	vector2D hitBoxWidth = { hitBox->size.x, 0 };
	vector2D hitBoxHeight = { 0, hitBox->size.y };
	vector2D totalOffset = OCT_vector2D_Vector2D(OCT_OP_ADD, hitBox->localOrigin, position2D_get(parentIndex)->globalPosition2D);

	point2D bottomLeft = OCT_vector2D_Vector2DMulti(3, OCT_OP_ADD, totalOffset, hitBox->localOrigin, OCT_vector2D_Scalar(OCT_OP_DIVIDE, hitBox->size, -2.0f));
	point2D bottomRight = OCT_vector2D_Vector2D(OCT_OP_ADD, bottomLeft, hitBoxWidth);
	point2D topRight = OCT_vector2D_Vector2D(OCT_OP_ADD, bottomRight, hitBoxHeight);
	point2D topLeft = OCT_vector2D_Vector2D(OCT_OP_ADD, topRight, OCT_vector2D_Scalar(OCT_OP_MULTIPLY, hitBoxHeight, -1));

	printf("Generated vertices (%f, %f), (%f, %f), (%f, %f), (%f, %f)\n", bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, topRight.x, topRight.y, topLeft.x, topLeft.y);

	hitBox2DVertices newHitBoxVertices = {
		*hitBox2D_getCounter(),
		hitBox->poolIndex,
		hitBox->localOrigin,
		bottomLeft,
		bottomRight,
		topRight,
		topLeft
	};

	newHitBoxVertices.poolIndex = *hitBox2DVertices_getCounter();
	newHitBoxVertices.hitBoxIndex = hitBox->poolIndex;									
	hitBox->verticesIndex = newHitBoxVertices.poolIndex;					
	hitBox2DVertices_getPool()[*hitBox2DVertices_getCounter()] = newHitBoxVertices;					
	*hitBox2DVertices_getCounter() += 1;
	return newHitBoxVertices.poolIndex;
}

/// API

componentIndex OCT_hitBox2D_addNew(gameObjectIndex parentIndex) {
	return hitBox2D_addNew(parentIndex);
}

void OCT_hitBox2D_resize(gameObjectIndex parentIndex, float sizeX, float sizeY) {
	return hitBox2D_resize(parentIndex, sizeX, sizeY);
}