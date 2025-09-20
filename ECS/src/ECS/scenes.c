#include "ECS/scenes.h"
#include "ECS/componentTypes.h"

scene mainScene = { 0 };
scene* currentScene = &mainScene;

////////////////////////////////////////////////////////// get pools
gameObject* getGameObjectsPool() {
	return currentScene->gameObjectsPool;
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
////////////////////////////////////////////////////////// get components
gameObject* getGameObject(size_t objectIndex) {
	return &currentScene->gameObjectsPool[objectIndex];
}
gameObject* getParentObject(size_t objectIndex) {
	return &currentScene->gameObjectsPool[currentScene->gameObjectsPool[objectIndex].parentIndex];
}
position2D* getPosition2D(size_t objectIndex) {
	return &currentScene->position2DPool[currentScene->gameObjectsPool[objectIndex].positionIndex];
}
transform2D* getTransform2D(size_t objectIndex) {
	return &currentScene->transform2DPool[currentScene->gameObjectsPool[objectIndex].transformIndex];
}
hitBox2D* getHitBox2D(size_t objectIndex) {
	return &currentScene->hitBox2DPool[currentScene->gameObjectsPool[objectIndex].hitBoxIndex];
}
////////////////////////////////////////////////////////// get counters
size_t* getGameObjectsCounter() {
	return &currentScene->gameObjectsCounter;
}
size_t* getPosition2DCounter() {
	return &currentScene->position2DCounter;
}
size_t* getTransform2DCounter() {
	return &currentScene->transform2DCounter;
}
size_t* getHitBox2DCounter() {
	return &currentScene->hitBox2DCounter;
}
//////////////////////////////////////////////////////////