#include "scene.h"

scene mainScene = { 0 }; 
scene* currentScene = &mainScene;

rendererObject* rendererObject_getPool() {
	return currentScene->rendererObjectPool;
}

counter* rendererObject_getCounter() {
	return &currentScene->rendererObjectCounter;
}

rendererObject* rendererObject_get(rendererObjectIndex rendererObject) {
	return &rendererObject_getPool()[rendererObject];
}

