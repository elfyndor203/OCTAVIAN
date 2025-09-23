#include "ECS/gameObjects.h"
#include "ECS/scenes.h"

#include "ECS/components/hitBox2D.h"

vector2D defaultHitBox2D = { DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y };

componentIndex hitBox2DAddNew(gameObjectIndex parentIndex) {
	gameObject* parentObject = getGameObject(parentIndex);


	hitBox2D newHitBox2D = { 0 };											// create blank object
	getHitBox2DPool()[*getHitBox2DCounter()] = newHitBox2D;					// copy into pool

	newHitBox2D.poolIndex = *getHitBox2DCounter();							// can find itself
	newHitBox2D.parentIndex = parentIndex;									// can find its parent
	parentObject->componentsMask |= (1ULL << componentHitBox2D);			// parent object knows it exists
	parentObject->hitBoxIndex = newHitBox2D.poolIndex;						// parent can find it

	hitBox2DResize(newHitBox2D.poolIndex, DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y);

	*getHitBox2DCounter() += 1;												// update counter LAST
	printf("Added new hitBox2D to object %zu \n", parentIndex);
	return newHitBox2D.poolIndex;
}

void hitBox2DReposition(gameObjectIndex parentIndex) {
	hitBox2D* hitBox = getHitBox2D(parentIndex);
	hitBox-> = getPosition2D(parentIndex)->globalPosition2D; 
}

void hitBox2DResize(gameObjectIndex parentIndex, float sizeX, float sizeY) {
	getHitBox2D(parentIndex)->size.x = sizeX;
	getHitBox2D(parentIndex)->size.y = sizeY;

	hitBox2DGenerateVertices(parentIndex);
}

subcomponentIndex hitBox2DGenerateVertices(gameObjectIndex parentIndex) {
	hitBox2D* hitBox = getHitBox2D(parentIndex);
	vector2D hitBoxWidth = { hitBox->size.x, 0 };
	vector2D hitBoxHeight = { 0, hitBox->size.y };

	point2D bottomLeft = addVectors2D(2, hitBox->localOrigin, vector2DScalarElementWise(&hitBox->size, -2.0f, divideFloats));
	point2D bottomRight = addVectors2D(2, bottomLeft, hitBoxWidth);
	point2D topRight = addVectors2D(2, bottomRight, hitBoxHeight);
	point2D topLeft = addVectors2D(2, topRight, vector2DScalarElementWise(&hitBoxHeight, -1, multiplyFloats));

	printf("Generated vertices (%f, %f), (%f, %f), (%f, %f), (%f, %f)\n", bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, topRight.x, topRight.y, topLeft.x, topLeft.y);

	hitBox2DVertices newHitBoxVertices = {
		*getHitBox2DCounter(),
		hitBox->poolIndex,
		hitBox->localOrigin,
		bottomLeft,
		bottomRight,
		topRight,
		topLeft
	};

	newHitBoxVertices.poolIndex = *getHitBox2DVerticesCounter();
	newHitBoxVertices.hitBoxIndex = hitBox->poolIndex;									
	hitBox->verticesIndex = newHitBoxVertices.poolIndex;					
	getHitBox2DVerticesPool()[*getHitBox2DVerticesCounter()] = newHitBoxVertices;					
	*getHitBox2DVerticesCounter() += 1;
	return newHitBoxVertices.poolIndex;
}

