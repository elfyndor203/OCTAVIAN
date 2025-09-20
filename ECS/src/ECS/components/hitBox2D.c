#include "ECS/gameObjects.h"
#include "ECS/scenes.h"

#include "ECS/components/hitBox2D.h"

vector2D defaultHitBox2D = { DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y };

size_t hitBox2DAddNew(size_t parentIndex) {
	gameObject* parentObject = getGameObject(parentIndex);

	hitBox2D newHitBox2D = { 0 };				// initialize to 0
	newHitBox2D.poolIndex = *getHitBox2DCounter();	// can find itself
	newHitBox2D.parentIndex = parentIndex;		// can find its parent

	parentObject->componentsMask |= (1ULL << componentHitBox2D);			// parent object knows it exists
	parentObject->hitBoxIndex = newHitBox2D.poolIndex;						// parent can find it

	hitBox2DResize(newHitBox2D.poolIndex, DEFAULT_HITBOX_X, DEFAULT_HITBOX_Y);

	getHitBox2DPool()[*getHitBox2DCounter()] = newHitBox2D;
	*getHitBox2DCounter() += 1;

	printf("Added new hitBox2D to object %zu \n", parentIndex);
	return newHitBox2D.poolIndex;
}

void hitBox2DResize(size_t parentIndex, float sizeX, float sizeY) {
	hitBox2D* hitBoxToInit = getHitBox2D(parentIndex);
	vector2D* bottomLeft = &hitBoxToInit->bottomLeft;

	bottomLeft->x = -sizeX / 2;
	bottomLeft->y = -sizeY / 2;

	printf("hitBox2D of gameObject %zu resized to %f, %f \n", parentIndex, getHitBox2D(parentIndex)->bottomLeft.x, bottomLeft->y);
}

hitBoxVertices hitBox2DGenerateVertices(size_t parentIndex) {
	hitBox2D* hitBox = getHitBox2D(parentIndex);
	
	printf("hitbox parentIndex: %zu\n", parentIndex);
	printf("hitbox parent bitmask: %"PRIu64" \n", getGameObject(parentIndex)->componentsMask);
	
	hitBoxVertices newHitBoxVertices = { 0 };
	newHitBoxVertices.poolIndex = *getHitBox2DCounter();

	printf("bottom left: (%f, %f)\n", hitBox->bottomLeft.x, hitBox->bottomLeft.y);

	vector2D hitBoxWidth = { -hitBox->bottomLeft.x, 0 };
	vector2D hitBoxHeight = { -hitBox->bottomLeft.y, 0 };

	point2D bottomLeft = getHitBox2D(parentIndex)->bottomLeft;
	point2D bottomRight = addVectors2D(2, bottomLeft, hitBoxWidth);
	point2D topRight = addVectors2D(2, bottomRight, hitBoxHeight);
	point2D topLeft = addVectors2D(2, topRight, vector2DScalarElementWise(&hitBoxHeight, -1, addFloats));

	printf("Generated vertices (%f, %f), (%f, %f), (%f, %f), (%f, %f)\n", bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, topRight.x, topRight.y, topLeft.x, topLeft.y);
	printf("HITBOX INDEX OF OBJECT %zu: %zu \n", parentIndex, getGameObject(parentIndex)->hitBoxIndex);
}

