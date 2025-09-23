#include "ECS/gameObjects.h"
#include "ECS/scenes.h"

#include "ECS/components/transform2D.h"

vector2D defaultScale = { DEFAULT_SCALE_X, DEFAULT_SCALE_Y };

componentIndex transform2DAddNew(gameObjectIndex parentIndex) {
	if (gameObjectHasComponent(parentIndex, componentTransform2D)) {
		logError(WARNING_REPLACED_COMPONENT);
	}
	gameObject* parentObject = getGameObject(parentIndex);

	transform2D newTransform2D = { 0 };
	newTransform2D.poolIndex = *getTransform2DCounter();
	newTransform2D.parentIndex = parentIndex;

	parentObject->componentsMask |= (1ULL << componentTransform2D);
	parentObject->transformIndex = newTransform2D.poolIndex;

	newTransform2D.rotation = DEFAULT_ROTATION;
	newTransform2D.scale = defaultScale;

	getTransform2DPool()[*getTransform2DCounter()] = newTransform2D;
	*getTransform2DCounter() += 1;

	printf("Added new transform2D to object %zu \n", parentIndex);
	return newTransform2D.poolIndex;
}