#include "ECS/gameObjects.h"

#include "ECS/components/position2D.h"

size_t createGameObject(size_t parentIndex, bool is3D) {
	gameObject* parentObject = &gameObjectsPool[parentIndex];

	gameObject newGameObject = { 0 };	
	
	if (is3D) {
		logError(EXIT_3D_NOT_SUPPORTED);										// change this later
	}
	else {
		newGameObject.poolIndex = gameObjectsCounter;							// it can find itself						
		newGameObject.parentIndex = parentIndex;								// it can find its parent

		parentObject->componentsMask |= (1ULL << componentChildObject);			// parent object knows it exists
//		parentObject->childIndex = newGameObject.poolIndex;						// parent object doesn't care where it is in the pool because there can be as many children as wanted
		
		addNewPosition2D(newGameObject.poolIndex);
	}

	gameObjectsPool[gameObjectsCounter] = newGameObject;
	gameObjectsCounter += 1;

	return newGameObject.poolIndex;
}







