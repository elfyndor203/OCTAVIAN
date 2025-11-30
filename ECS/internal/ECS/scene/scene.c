#include "scene_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"

iOCT_counter sceneCounter = 0;

////////////////////////////////////////////////////////// scene logic 
iOCT_scene* iOCT_scene_get(iOCT_sceneID sceneID) {
	if (sceneID > iOCT_MAX_SCENES || OCT_scenePool[sceneID] == 0) {
		OCT_logError(ERR_SCENE_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	printf("Got scene #%zu\n", sceneID);
	return OCT_scenePool[sceneID];
}

iOCT_sceneID iOCT_scene_new() {
	iOCT_scene* newScene = calloc(1, sizeof(iOCT_scene));
	if (!newScene) {
		OCT_logError(EXIT_SCENE_FAILED);				//NOTE: 2 EXITS
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
		return 0;
	}

	else {
		newScene->sceneID = sceneCounter;
		iOCT_gameObject blankRootObject = { 0 };
		blankRootObject.hitBoxID = iOCT_NO_COMPONENT;		// NOTE_NEW_COMPONENTS
		blankRootObject.componentsMask |= (1ULL << componentParentObject);
		blankRootObject.componentsMask |= (1ULL << componentPosition2D);
		blankRootObject.componentsMask |= (1ULL << componentTransform2D);
		newScene->rootObject = blankRootObject;
	}

	OCT_scenePool[sceneCounter] = newScene;		// store scene
	iOCT_sceneID sceneID = sceneCounter;	//
	newScene->sceneID = sceneCounter;		// log own index
	sceneCounter += 1;						// update counter
	
	printf("Created scene with sceneID %zu\n", sceneID);
	return sceneID;
}

void iOCT_scene_setCurrent(iOCT_sceneID sceneID) {
	OCT_currentScene = iOCT_scene_get(sceneID);
}

void iOCT_scene_initialize() {
	memset(OCT_scenePool, 0, sizeof(OCT_scenePool));
	printf("Scene pool zeroed out\n");
}



