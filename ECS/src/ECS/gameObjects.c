#include "ECS/gameObjects.h"
#include "ECS/scenes.h"

#include "ECS/components/position2D.h"		// two required components
#include "ECS/components/transform2D.h"

gameObjectIndex gameObjectCreateNew(gameObjectIndex parentIndex, bool is3D) {
	gameObject* parentObject = getGameObject(parentIndex);

	gameObject newGameObject = { 0 };	
	
	if (is3D) {
		logError(EXIT_3D_NOT_SUPPORTED);										// change this later
	}
	else {
		newGameObject.poolIndex = *getGameObjectsCounter();							// it can find itself						
		newGameObject.parentIndex = parentIndex;								// it can find its parent

		parentObject->componentsMask |= (1ULL << componentChildObject);			// parent object knows it exists
//		parentObject->childIndex = newGameObject.poolIndex;						// parent object doesn't care where it is in the pool because there can be as many children as wanted
	}

	getGameObjectsPool()[*getGameObjectsCounter()] = newGameObject;
	*getGameObjectsCounter() += 1;

	position2DAddNew(newGameObject.poolIndex);
	transform2DAddNew(newGameObject.poolIndex);

	printf("\nCreated new gameObject as a child of object %zu \n", parentIndex);
	return newGameObject.poolIndex;
}

bool gameObjectHasComponent(gameObjectIndex gameObject, componentTypes component) {
	if (getGameObject(gameObject)->componentsMask & (1ULL << component)) {// creates a new uint_64 with a 1 at the component # bit and compares bitwise
		printf("gameObject %zu DOES have componentTypes component #%d\n", gameObject, component);
		return true;
	}
	printf("gameObject %zu does NOT have componentTypes component #%d\n", gameObject, component);
	return false;
}







