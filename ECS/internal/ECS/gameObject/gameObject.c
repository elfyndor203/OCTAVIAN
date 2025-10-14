#include "gameObject.h"
#include "ECS/scene/scene.h"

#include "ECS/components/position2D/position2D.h"		// two required components
#include "ECS/components/transform2D/transform2D.h"

gameObjectIndex gameObject_createNew(gameObjectIndex parentIndex, bool is3D) {
	gameObject* parentObject = gameObject_get(parentIndex);

	gameObject newGameObject = { 0 };	
	
	if (is3D) {
		logError(EXIT_3D_NOT_SUPPORTED);										// change this later
	}
	else {
		newGameObject.poolIndex = *gameObject_getCounter();							// it can find itself						
		newGameObject.parentIndex = parentIndex;								// it can find its parent

		parentObject->componentsMask |= (1ULL << componentChildObject);			// parent object knows it exists
//		parentObject->childIndex = newGameObject.poolIndex;						// parent object doesn't care where it is in the pool because there can be as many children as wanted
	}

	gameObject_getPool()[*gameObject_getCounter()] = newGameObject;
	*gameObject_getCounter() += 1;

	position2D_addNew(newGameObject.poolIndex);
	transform2D_addNew(newGameObject.poolIndex);

	printf("\nCreated new gameObject as a child of object %zu \n", parentIndex);
	return newGameObject.poolIndex;
}

bool gameObject_hasComponent(gameObjectIndex gameObject, componentTypes component) {
	if (gameObject_get(gameObject)->componentsMask & (1ULL << component)) {// creates a new uint_64 with a 1 at the component # bit and compares bitwise
		printf("gameObject %zu DOES have componentTypes component #%d\n", gameObject, component);
		return true;
	}
	printf("gameObject %zu does NOT have componentTypes component #%d\n", gameObject, component);
	return false;
}







