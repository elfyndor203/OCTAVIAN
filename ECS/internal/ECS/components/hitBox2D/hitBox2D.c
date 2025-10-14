#include "hitBox2D.h"

#include "ECS/gameObject/gameObject.h"
#include "ECS/scene/scene.h"


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
	vector2D totalOffset = vector2D_addV(2, hitBox->localOrigin, position2D_get(parentIndex)->globalPosition2D);

	point2D bottomLeft = vector2D_addV(3, totalOffset, hitBox->localOrigin, vector2D_elementWiseS(&hitBox->size, -2.0f, floats_divide));
	point2D bottomRight = vector2D_addV(2, bottomLeft, hitBoxWidth);
	point2D topRight = vector2D_addV(2, bottomRight, hitBoxHeight);
	point2D topLeft = vector2D_addV(2, topRight, vector2D_elementWiseS(&hitBoxHeight, -1, floats_multiply));

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
	getHitBox2DVerticesPool()[*hitBox2DVertices_getCounter()] = newHitBoxVertices;					
	*hitBox2DVertices_getCounter() += 1;
	return newHitBoxVertices.poolIndex;
}

