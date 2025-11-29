#include "gameObject_internal.h"
#include "ECS/scene/scene_internal.h"

#include "ECS/components/position2D/position2D_internal.h"		// two required components
#include "ECS/components/transform2D/transform2D_internal.h"

OCT_gameObjectID gameObject_createNew(OCT_gameObjectID parentIndex, bool is3D) {
	gameObject* parentObject = gameObject_get(parentIndex);

	gameObject newGameObject = { 0 };	//NOTE_NEW_COMPONENTS
	newGameObject.hitBoxIndex = OCT_NO_COMPONENT;
	
	if (is3D) {
		OCT_logError(EXIT_3D_NOT_SUPPORTED);										// change this later
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

bool gameObject_hasComponent(OCT_gameObjectID gameObject, componentTypes component) {
	if (gameObject_get(gameObject)->componentsMask & (1ULL << component)) {// creates a new uint_64 with a 1 at the component # bit and compares bitwise
		printf("gameObject %zu DOES have componentTypes component #%d\n", gameObject, component);
		return true;
	}
	printf("gameObject %zu does NOT have componentTypes component #%d\n", gameObject, component);
	return false;
}

gameObject gameObject_generateRoot() {
	gameObject rootObject = { 0 };
	rootObject.hitBoxIndex = OCT_NO_COMPONENT;		// NOTE_NEW_COMPONENTS
	rootObject.componentsMask |= (1ULL << componentParentObject);
	rootObject.componentsMask |= (1ULL << componentPosition2D);
	rootObject.componentsMask |= (1ULL << componentTransform2D);
	return rootObject;
}

/// API

OCT_gameObjectID OCT_gameObject_createNew(OCT_gameObjectID parentIndex, bool is3D) {
	return gameObject_createNew(parentIndex, is3D);
}

bool OCT_gameObject_hasComponent(OCT_gameObjectID gameObject, componentTypes component) {
	return gameObject_hasComponent(gameObject, component);
}







