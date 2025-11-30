#include "gameObject_internal.h"
#include "ECS/scene/scene_internal.h"

#include "ECS/components/position2D/position2D_internal.h"		// two required components
#include "ECS/components/transform2D/transform2D_internal.h"

////////////////////////////////////////////////////////// getter functions
iOCT_gameObject* iOCT_gameObject_get(iOCT_sceneID sceneID, iOCT_gameObjectID gameObjectID) {
	// check if scene exists, then if object exists within that scene
	if (iOCT_scene_get(sceneID) == iOCT_GET_FAILED || gameObjectID > iOCT_scene_get(sceneID)->gameObjectCounter) {	
		OCT_logError(ERR_GAMEOBJECT_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	printf("Got gameObject #%zu from scene #%zu\n", gameObjectID, sceneID);
	return &iOCT_scene_get(sceneID)->gameObjectPool[gameObjectID];	// access the scene, access the gameObject, and return its pointer
}

iOCT_gameObject* iOCT_gameObject_getPool(iOCT_sceneID sceneID) {
	if (iOCT_scene_get(sceneID) == iOCT_GET_FAILED) {
		OCT_logError(ERR_GAMEOBJECTPOOL_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	printf("Got gameObjectPool from scene #%zu\n", sceneID);
	return &iOCT_scene_get(sceneID)->gameObjectPool;
}

iOCT_counter* iOCT_gameObject_getCounter(iOCT_sceneID sceneID) {
	if (iOCT_scene_get(sceneID) == iOCT_GET_FAILED) {
		OCT_logError(ERR_GAMEOBJECTCOUNTER_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	printf("Got gameObjectCounter from scene #%zu\n", sceneID);
	return &iOCT_scene_get(sceneID)->gameObjectCounter;
}
////////////////////////////////////////////////////////// getter functions

iOCT_gameObjectID iOCT_gameObject_createNew(iOCT_sceneID sceneID, iOCT_gameObjectID parentID) {
	if (iOCT_getCounter(sceneID) >= iOCT_MAX_GAMEOBJECTS - 1) {
		logError(ERR_GAMEOBJECTPOOL_FULL);
		return iOCT_GAMEOBJECT_FAILED;
	}
	iOCT_gameObject newGameObject = { 0 };

	iOCT_gameObject* parentObject = iOCT_gameObject_get(sceneID, parentID);	// store pointer to its parent
	parentObject->componentsMask |= (1ULL << componentChildObject);				// parent object knows it exists

	iOCT_gameObjectID gameObjectID = *iOCT_gameObject_getCounter(sceneID);	// setting default values
	newGameObject.sceneID = sceneID;
	newGameObject.gameObjectID = gameObjectID;								// it can find itself			
	newGameObject.parentID = parentID;								// it can find its parent
	newGameObject.positionID = iOCT_NO_COMPONENT;
	newGameObject.transformID = iOCT_NO_COMPONENT;
	newGameObject.hitBoxID = iOCT_NO_COMPONENT;							// 	

	iOCT_gameObject_getPool(sceneID)[*iOCT_gameObject_getCounter(sceneID)] = newGameObject;	// store function before adding requirements
	*iOCT_gameObject_getCounter(sceneID) += 1;

	position2D_addNew(gameObjectID);							// add requirements to the stored object
	transform2D_addNew(gameObjectID);

	printf("\nCreated new gameObject #%zu in scene #%zu as a child of object %zu \n", gameObjectID, sceneID, parentID);
	return gameObjectID;
}

bool iOCT_gameObject_hasComponent(iOCT_sceneID sceneID, iOCT_gameObjectID gameObjectID, componentTypes component) {
	if (iOCT_gameObject_get(sceneID, gameObjectID)->componentsMask & (1ULL << component)) {// creates a new uint_64 with a 1 at the component # bit and compares bitwise
		printf("gameObject %zu DOES have componentTypes component #%d\n", gameObjectID, component);
		return true;
	}
	printf("gameObject %zu does NOT have componentTypes component #%d\n", gameObjectID, component);
	return false;
}

/// API








