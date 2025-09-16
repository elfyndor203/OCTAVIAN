#include "ECS/gameObjects.h"

#include "ECS/components/transform2D.h"

vector2D defaultScale = { DEFAULT_SCALE_X, DEFAULT_SCALE_Y };

size_t addNewTransform2D(size_t parentIndex) {
	gameObject* parentObject = &gameObjectsPool[parentIndex];

	transform2D newTransform2D = { 0 };
	newTransform2D.poolIndex = transform2DCounter;
	newTransform2D.parentIndex = parentIndex;

	parentObject->componentsMask |= (1ULL << componentTransform2D);
	parentObject->transformIndex = newTransform2D.poolIndex;

	newTransform2D.rotation = DEFAULT_ROTATION;
	newTransform2D.scale = defaultScale;

	transform2DPool[transform2DCounter] = newTransform2D;
	transform2DCounter += 1;
	return newTransform2D.poolIndex;
}