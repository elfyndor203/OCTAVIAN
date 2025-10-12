#include "renderer/scenes.h"
#include "renderer/rendererObject.h"

scene mainScene = { 0 }; 
scene* currentScene = &mainScene;

rendererObject* getRendererObjectPool() {
	return currentScene->rendererObjectPool;
}

counter* getRendererObjectCounter() {
	return &currentScene->rendererObjectCounter;
}
