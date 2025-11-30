#include "position2D_internal.h"

#include "ECS/gameObject/gameObject_internal.h"
#include "ECS/scene/scene_internal.h"

size_t iOCT_MAX_POSITION2D = iOCT_DEFAULT_MAX_GAMEOBJECTS;

OCT_vector2D defaultPosition2D = { DEFAULT_POSITION_X, DEFAULT_POSITION_Y };

iOCT_position2D* iOCT_position2D_get(iOCT_sceneID sceneID, iOCT_gameObjectID parentID) {
	iOCT_scene* scene = iOCT_scene_get(sceneID);
	if (scene == iOCT_GET_FAILED || parentID >= scene->gameObjectCounter) {
		OCT_logError(ERR_POSITION2D_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	iOCT_gameObject* parentObject = iOCT_gameObject_get(sceneID, parentID);
	if (parentObject == iOCT_GET_FAILED) {
		OCT_logError(ERR_POSITION2D_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	if (parentObject->positionID == iOCT_NO_COMPONENT) {
		OCT_logError(ERR_POSITION2D_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	printf("Got position2D from gameObject #%zu from scene #%zu\n", parentID, sceneID);
	return &scene->position2DPool[parentObject->positionID];
}

iOCT_position2D* iOCT_position2D_getPool(iOCT_sceneID sceneID) {
	iOCT_scene* scene = iOCT_scene_get(sceneID);
	if (scene == iOCT_GET_FAILED) {
		OCT_logError(ERR_POSITION2DPOOL_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	printf("Got position2D pool from scene #%zu\n", sceneID);
	return scene->position2DPool; // array decay to pointer
}
iOCT_counter* iOCT_position2D_getCounter(iOCT_sceneID sceneID) {
	iOCT_scene* scene = iOCT_scene_get(sceneID);
	if (scene == iOCT_GET_FAILED) {
		OCT_logError(ERR_POSITION2DCOUNTER_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	printf("Got position2D counter from scene #%zu\n", sceneID);
	return &scene->position2DCounter;
}

iOCT_componentID iOCT_position2D_addNew(iOCT_sceneID sceneID, iOCT_gameObjectID parentID) {								// attaches a new default position2D to some gameObject
	if (iOCT_gameObject_hasComponent(sceneID, parentID, componentPosition2D)) {
		OCT_logError(WARNING_COMPONENT_REPLACED);
	}
	iOCT_counter* counter = iOCT_transform2D_getCounter(sceneID);
	if (*counter >= iOCT_MAX_POSITION2D) {
		logError(ERR_POSITION2DPOOL_FULL);
		return iOCT_POSITION2D_FAILED;
	}

	iOCT_position2D newPosition2D = { 0 };

	iOCT_gameObject* parentObject = iOCT_gameObject_get(sceneID, parentID);
	parentObject->componentsMask |= (1ULL << componentPosition2D);		// parent object knows it exists

	iOCT_componentID positionID = *counter;		// setting values
	newPosition2D.positionID = positionID;									// it can find itself
	newPosition2D.parentID = parentID;										// it can find its parent object
	parentObject->positionID = newPosition2D.positionID;					// parent object can find it
	newPosition2D.globalPosition2D = defaultPosition2D;						// default values
	newPosition2D.localPosition2D = defaultPosition2D;

	iOCT_position2D_getPool(sceneID)[*counter] = newPosition2D;			// add it to the pool
	*counter += 1;

	printf("Added new position2D to object #%zu in scene #%zu\n", parentID, sceneID);
	return positionID;
}