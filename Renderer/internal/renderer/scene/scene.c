#include "scene_internal.h"

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

/// API

rendererObject* OCT_rendererObject_getPool() {
		return rendererObject_getPool();
}
counter* OCT_rendererObject_getCounter() {
		return rendererObject_getCounter();
}
rendererObject* OCT_rendererObject_get(rendererObjectIndex rendererObjectIndex) {
		return rendererObject_get(rendererObjectIndex);
}

void test_function() {
	printf("test function called\n");
}