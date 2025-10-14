#include "scene.h"
#include "ECS/components/componentTypes/componentTypes.h"

scene mainScene = { 0 };
scene* currentScene = &mainScene;

////////////////////////////////////////////////////////// get pools
gameObject* getGameObjectPool() {
	return currentScene->gameObjectPool;
}
position2D* getPosition2DPool() {
	return currentScene->position2DPool;
}
transform2D* getTransform2DPool() {
	return currentScene->transform2DPool;
}
hitBox2D* getHitBox2DPool() {
	return currentScene->hitBox2DPool;
}

hitBox2DVertices* getHitBox2DVerticesPool() {
	return currentScene->hitBox2DVerticesPool;
}
////////////////////////////////////////////////////////// get components
gameObject* getGameObject(gameObjectIndex objectIndex) {
	return &currentScene->gameObjectPool[objectIndex];
}
gameObject* getParentObject(gameObjectIndex objectIndex) {
	return &currentScene->gameObjectPool[currentScene->gameObjectPool[objectIndex].parentIndex];
}
position2D* getPosition2D(gameObjectIndex objectIndex) {
	return &currentScene->position2DPool[currentScene->gameObjectPool[objectIndex].positionIndex];
}
transform2D* getTransform2D(gameObjectIndex objectIndex) {
	return &currentScene->transform2DPool[currentScene->gameObjectPool[objectIndex].transformIndex];
}
hitBox2D* getHitBox2D(gameObjectIndex objectIndex) {
	return &currentScene->hitBox2DPool[currentScene->gameObjectPool[objectIndex].hitBoxIndex];
}

hitBox2DVertices* getHitBox2DVertices(gameObjectIndex objectIndex) {
	return &currentScene->hitBox2DVerticesPool[currentScene->hitBox2DPool[currentScene->gameObjectPool[objectIndex].hitBoxIndex].verticesIndex];
}

////////////////////////////////////////////////////////// get counters
counter* gameObjectGetCounter() {
	return &currentScene->gameObjectCounter;
}
counter* getPosition2DCounter() {
	return &currentScene->position2DCounter;
}
counter* getTransform2DCounter() {
	return &currentScene->transform2DCounter;
}
counter* getHitBox2DCounter() {
	return &currentScene->hitBox2DCounter;
}
counter* getHitBox2DVerticesCounter() {
	return &currentScene->hitBox2DVerticesCounter;
}
//////////////////////////////////////////////////////////