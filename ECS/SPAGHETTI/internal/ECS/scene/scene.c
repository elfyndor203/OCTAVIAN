#include "scene_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"

iOCT_scene* currentScene;
iOCT_counter sceneCounter = 0;

////////////////////////////////////////////////////////// scene logic 
iOCT_scene* scene_get(iOCT_sceneID sceneID) {
	return scenePool[sceneID];
}

iOCT_sceneID scene_new() {
	iOCT_scene* newScene = calloc(1, sizeof(iOCT_scene));
	
	if (!newScene) {
		OCT_logError(EXIT_SCENE_FAILED);
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
		return 0;
	}
	else {
		newScene->sceneID = sceneCounter;
		newScene->rootObject = gameObject_generateRoot();
	}
	scenePool[sceneCounter] = newScene;
	iOCT_sceneID sceneID = sceneCounter;
	sceneCounter += 1;
	return sceneID;
}

void scene_setCurrent(iOCT_sceneID sceneID) {
	currentScene = scene_get(sceneID);
}

////////////////////////////////////////////////////////// get pools
iOCT_gameObject* gameObject_getPool() {
	return currentScene->gameObjectPool;
}
iOCT_position2D* position2D_getPool() {
	return currentScene->position2DPool;
}
iOCT_transform2D* transform2D_getPool() {
	if (!currentScene->transform2DPool) {
		OCT_logError(EXIT_TRANSFORM_COUNTER_FAILED);
		return NULL;
	}
	else {
		return currentScene->transform2DPool;
	}
}
iOCT_hitBox2D* hitBox2D_getPool() {
	return currentScene->hitBox2DPool;
}

hitBox2DVertices* hitBox2DVertices_getPool() {
	return currentScene->hitBox2DVerticesPool;
}
////////////////////////////////////////////////////////// get components
iOCT_gameObject* gameObject_get(OCT_gameObjectID objectIndex) {
	return &currentScene->gameObjectPool[objectIndex];
}

iOCT_gameObject* gameObject_getParentObject(OCT_gameObjectID objectIndex) {
	return &currentScene->gameObjectPool[currentScene->gameObjectPool[objectIndex].parentIndex];
}
iOCT_position2D* position2D_get(OCT_gameObjectID objectIndex) {
	return &currentScene->position2DPool[currentScene->gameObjectPool[objectIndex].positionIndex];
}
iOCT_transform2D* transform2D_get(OCT_gameObjectID objectIndex) {
	return &currentScene->transform2DPool[currentScene->gameObjectPool[objectIndex].transformIndex];
}
iOCT_hitBox2D* hitBox2D_get(OCT_gameObjectID objectIndex) {
	return &currentScene->hitBox2DPool[currentScene->gameObjectPool[objectIndex].hitBoxIndex];
}

hitBox2DVertices* hitBox2DVertices_get(OCT_gameObjectID objectIndex) {
	return &currentScene->hitBox2DVerticesPool[currentScene->hitBox2DPool[currentScene->gameObjectPool[objectIndex].hitBoxIndex].verticesIndex];
}

////////////////////////////////////////////////////////// get counters
iOCT_counter* gameObject_getCounter() {
	return &currentScene->gameObjectCounter;
}
iOCT_counter* position2D_getCounter() {
	return &currentScene->position2DCounter;
}
iOCT_counter* transform2D_getCounter() {
	return &currentScene->transform2DCounter;
}
iOCT_counter* hitBox2D_getCounter() {
	return &currentScene->hitBox2DCounter;
}
iOCT_counter* hitBox2DVertices_getCounter() {
	return &currentScene->hitBox2DVerticesCounter;
}
//////////////////////////////////////////////////////////

/// API

////////////////////////////////////////////////////////// scene
iOCT_scene* OCT_scene_get(iOCT_sceneID sceneID) {
	return scene_get(sceneID);
}
iOCT_sceneID OCT_scene_new(OCT_gameObjectID rootObject) {
	return scene_new(rootObject);
}
void OCT_scene_setCurrent(iOCT_sceneID sceneID) {
	scene_setCurrent(sceneID);
}
////////////////////////////////////////////////////////// pools
iOCT_gameObject* OCT_gameObject_getPool() {
	return gameObject_getPool();
}
iOCT_position2D* OCT_position2D_getPool() {
	return position2D_getPool();
}
iOCT_transform2D* OCT_transform2D_getPool() {

	return transform2D_getPool();
}
iOCT_hitBox2D* OCT_hitBox2D_getPool() {
	return hitBox2D_getPool();
}

hitBox2DVertices* OCT_hitBox2DVertices_getPool() {
	return hitBox2DVertices_getPool();
}

////////////////////////////////////////////////////////// objects and components
iOCT_gameObject* OCT_gameObject_get(OCT_gameObjectID objectIndex) {
	return gameObject_get(objectIndex);
}
iOCT_gameObject* OCT_gameObject_getParentObject(OCT_gameObjectID objectIndex) {
	return gameObject_getParentObject(objectIndex);
}
iOCT_position2D* OCT_position2D_get(OCT_gameObjectID objectIndex) {
	return position2D_get(objectIndex);
}
iOCT_transform2D* OCT_transform2D_get(OCT_gameObjectID objectIndex) {
	return transform2D_get(objectIndex);
}
iOCT_hitBox2D* OCT_hitBox2D_get(OCT_gameObjectID objectIndex) {
	return hitBox2D_get(objectIndex);
}

// Subcomponent getters
hitBox2DVertices* OCT_hitBox2DVertices_get(OCT_gameObjectID objectIndex) {
	return hitBox2DVertices_get(objectIndex);
}

// Counter getters
iOCT_counter* OCT_gameObject_getCounter() {
	return gameObject_getCounter();
}
iOCT_counter* OCT_position2D_getCounter() {
	return position2D_getCounter();
}
iOCT_counter* OCT_transform2D_getCounter() {
	return transform2D_getCounter();
}
iOCT_counter* OCT_hitBox2D_getCounter() {
	return hitBox2D_getCounter();
}
iOCT_counter* OCT_hitBox2DVertices_getCounter() {
	return hitBox2DVertices_getCounter();
}
