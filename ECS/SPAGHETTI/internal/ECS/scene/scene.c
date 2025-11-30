#include "scene_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"

scene* currentScene;
OCT_counter sceneCounter = 0;

////////////////////////////////////////////////////////// scene logic 
scene* scene_get(OCT_sceneID sceneID) {
	return scenePointerPool[sceneID];
}

OCT_sceneID scene_new() {
	scene* newScene = calloc(1, sizeof(scene));
	
	if (!newScene) {
		OCT_logError(EXIT_SCENE_FAILED);
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
		return 0;
	}
	else {
		newScene->sceneID = sceneCounter;
		newScene->rootObject = gameObject_generateRoot();
	}
	scenePointerPool[sceneCounter] = newScene;
	OCT_sceneID sceneID = sceneCounter;
	sceneCounter += 1;
	return sceneID;
}

void scene_setCurrent(OCT_sceneID sceneID) {
	currentScene = scene_get(sceneID);
}

////////////////////////////////////////////////////////// get pools
gameObject* gameObject_getPool() {
	return currentScene->gameObjectPool;
}
position2D* position2D_getPool() {
	return currentScene->position2DPool;
}
transform2D* transform2D_getPool() {
	if (!currentScene->transform2DPool) {
		OCT_logError(EXIT_TRANSFORM_COUNTER_FAILED);
		return NULL;
	}
	else {
		return currentScene->transform2DPool;
	}
}
hitBox2D* hitBox2D_getPool() {
	return currentScene->hitBox2DPool;
}

hitBox2DVertices* hitBox2DVertices_getPool() {
	return currentScene->hitBox2DVerticesPool;
}
////////////////////////////////////////////////////////// get components
gameObject* gameObject_get(OCT_gameObjectID objectIndex) {
	return &currentScene->gameObjectPool[objectIndex];
}

gameObject* gameObject_getParentObject(OCT_gameObjectID objectIndex) {
	return &currentScene->gameObjectPool[currentScene->gameObjectPool[objectIndex].parentIndex];
}
position2D* position2D_get(OCT_gameObjectID objectIndex) {
	return &currentScene->position2DPool[currentScene->gameObjectPool[objectIndex].positionIndex];
}
transform2D* transform2D_get(OCT_gameObjectID objectIndex) {
	return &currentScene->transform2DPool[currentScene->gameObjectPool[objectIndex].transformIndex];
}
hitBox2D* hitBox2D_get(OCT_gameObjectID objectIndex) {
	return &currentScene->hitBox2DPool[currentScene->gameObjectPool[objectIndex].hitBoxIndex];
}

hitBox2DVertices* hitBox2DVertices_get(OCT_gameObjectID objectIndex) {
	return &currentScene->hitBox2DVerticesPool[currentScene->hitBox2DPool[currentScene->gameObjectPool[objectIndex].hitBoxIndex].verticesIndex];
}

////////////////////////////////////////////////////////// get counters
OCT_counter* gameObject_getCounter() {
	return &currentScene->gameObjectCounter;
}
OCT_counter* position2D_getCounter() {
	return &currentScene->position2DCounter;
}
OCT_counter* transform2D_getCounter() {
	return &currentScene->transform2DCounter;
}
OCT_counter* hitBox2D_getCounter() {
	return &currentScene->hitBox2DCounter;
}
OCT_counter* hitBox2DVertices_getCounter() {
	return &currentScene->hitBox2DVerticesCounter;
}
//////////////////////////////////////////////////////////

/// API

////////////////////////////////////////////////////////// scene
scene* OCT_scene_get(OCT_sceneID sceneID) {
	return scene_get(sceneID);
}
OCT_sceneID OCT_scene_new(OCT_gameObjectID rootObject) {
	return scene_new(rootObject);
}
void OCT_scene_setCurrent(OCT_sceneID sceneID) {
	scene_setCurrent(sceneID);
}
////////////////////////////////////////////////////////// pools
gameObject* OCT_gameObject_getPool() {
	return gameObject_getPool();
}
position2D* OCT_position2D_getPool() {
	return position2D_getPool();
}
transform2D* OCT_transform2D_getPool() {

	return transform2D_getPool();
}
hitBox2D* OCT_hitBox2D_getPool() {
	return hitBox2D_getPool();
}

hitBox2DVertices* OCT_hitBox2DVertices_getPool() {
	return hitBox2DVertices_getPool();
}

////////////////////////////////////////////////////////// objects and components
gameObject* OCT_gameObject_get(OCT_gameObjectID objectIndex) {
	return gameObject_get(objectIndex);
}
gameObject* OCT_gameObject_getParentObject(OCT_gameObjectID objectIndex) {
	return gameObject_getParentObject(objectIndex);
}
position2D* OCT_position2D_get(OCT_gameObjectID objectIndex) {
	return position2D_get(objectIndex);
}
transform2D* OCT_transform2D_get(OCT_gameObjectID objectIndex) {
	return transform2D_get(objectIndex);
}
hitBox2D* OCT_hitBox2D_get(OCT_gameObjectID objectIndex) {
	return hitBox2D_get(objectIndex);
}

// Subcomponent getters
hitBox2DVertices* OCT_hitBox2DVertices_get(OCT_gameObjectID objectIndex) {
	return hitBox2DVertices_get(objectIndex);
}

// Counter getters
OCT_counter* OCT_gameObject_getCounter() {
	return gameObject_getCounter();
}
OCT_counter* OCT_position2D_getCounter() {
	return position2D_getCounter();
}
OCT_counter* OCT_transform2D_getCounter() {
	return transform2D_getCounter();
}
OCT_counter* OCT_hitBox2D_getCounter() {
	return hitBox2D_getCounter();
}
OCT_counter* OCT_hitBox2DVertices_getCounter() {
	return hitBox2DVertices_getCounter();
}
