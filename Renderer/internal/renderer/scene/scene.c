#include "scene_internal.h"

iOCT_scene mainScene = { 0 }; 
iOCT_scene* OCT_currentScene = &mainScene;

rendererObject* rendererObject_getPool() {
	return OCT_currentScene->rendererObjectPool;
}

counter* rendererObject_getCounter() {
	return &OCT_currentScene->rendererObjectCounter;
}

rendererObject* rendererObject_get(OCT_rendererObjectID rendererObject) {
	printf("requesting rendererObject #%zu\n", rendererObject);
	return &rendererObject_getPool()[rendererObject];
}

/// API

rendererObject* OCT_rendererObject_getPool() {
		return rendererObject_getPool();
}
counter* OCT_rendererObject_getCounter() {
		return rendererObject_getCounter();
}
rendererObject* OCT_rendererObject_get(OCT_rendererObjectID OCT_rendererObjectID) {
		return rendererObject_get(OCT_rendererObjectID);
}