#include "ECS/gameObjects.h"
#include "ECS/scenes.h"

#include "ECS/components/position2D.h"

vector2D defaultPosition2D = { DEFAULT_POSITION2D_X, DEFAULT_POSITION2D_Y };

componentIndex position2DAddNew(size_t parentIndex) {								// attaches a new default position2D to some gameObject
	gameObject* parentObject = getGameObject(parentIndex);

	position2D newPosition2D = { 0 };							
	newPosition2D.poolIndex = *getPosition2DCounter();						// it can find itself
	newPosition2D.parentIndex = parentIndex;								// it can find its parent object

	parentObject->componentsMask |= (1ULL << componentPosition2D);			// parent object knows it exists
	parentObject->positionIndex = newPosition2D.poolIndex;					// parent object can find it

	newPosition2D.globalPosition2D = defaultPosition2D;						// default values
	newPosition2D.localPosition2D = defaultPosition2D;

	getPosition2DPool()[*getPosition2DCounter()] = newPosition2D;			// add it to the pool
	*getPosition2DCounter() += 1;

	printf("Added new position2D to object %zu \n", parentIndex);
	return newPosition2D.poolIndex;
}
