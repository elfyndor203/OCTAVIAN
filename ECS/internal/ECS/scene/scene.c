#include "scene.h"

#include "ECS/components/componentTypes/componentTypes.h"

scene mainScene = { 0 };
scene* currentScene = &mainScene;

////////////////////////////////////////////////////////// get pools
gameObject* gameObject_getPool() {
	return currentScene->gameObjectPool;
}
position2D* position2D_getPool() {
	return currentScene->position2DPool;
}
transform2D* transform2D_getPool() {
	return currentScene->transform2DPool;
}
hitBox2D* hitBox2D_getPool() {
	return currentScene->hitBox2DPool;
}

hitBox2DVertices* getHitBox2DVerticesPool() {
	return currentScene->hitBox2DVerticesPool;
}
////////////////////////////////////////////////////////// get components
gameObject* gameObject_get(gameObjectIndex objectIndex) {
	return &currentScene->gameObjectPool[objectIndex];
}
gameObject* gameObject_getParentObject(gameObjectIndex objectIndex) {
	return &currentScene->gameObjectPool[currentScene->gameObjectPool[objectIndex].parentIndex];
}
position2D* position2D_get(gameObjectIndex objectIndex) {
	return &currentScene->position2DPool[currentScene->gameObjectPool[objectIndex].positionIndex];
}
transform2D* transform2D_get(gameObjectIndex objectIndex) {
	return &currentScene->transform2DPool[currentScene->gameObjectPool[objectIndex].transformIndex];
}
hitBox2D* hitBox2D_get(gameObjectIndex objectIndex) {
	return &currentScene->hitBox2DPool[currentScene->gameObjectPool[objectIndex].hitBoxIndex];
}

hitBox2DVertices* hitBox2DVertices_get(gameObjectIndex objectIndex) {
	return &currentScene->hitBox2DVerticesPool[currentScene->hitBox2DPool[currentScene->gameObjectPool[objectIndex].hitBoxIndex].verticesIndex];
}

////////////////////////////////////////////////////////// get counters
counter* gameObject_getCounter() {
	return &currentScene->gameObjectCounter;
}
counter* position2D_getCounter() {
	return &currentScene->position2DCounter;
}
counter* transform2D_getCounter() {
	return &currentScene->transform2DCounter;
}
counter* hitBox2D_getCounter() {
	return &currentScene->hitBox2DCounter;
}
counter* hitBox2DVertices_getCounter() {
	return &currentScene->hitBox2DVerticesCounter;
}
//////////////////////////////////////////////////////////