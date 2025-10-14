#include "transform2D.h"

#include "ECS/gameObject/gameObject.h"
#include "ECS/scene/scene.h"

vector2D defaultScale = { DEFAULT_SCALE_X, DEFAULT_SCALE_Y };

componentIndex transform2D_addNew(gameObjectIndex parentIndex) {
	if (gameObject_hasComponent(parentIndex, componentTransform2D)) {
		logError(WARNING_COMPONENT_REPLACED);
	}
	gameObject* parentObject = gameObject_get(parentIndex);

	transform2D newTransform2D = { 0 };
	newTransform2D.poolIndex = *transform2D_getCounter();
	newTransform2D.parentIndex = parentIndex;

	parentObject->componentsMask |= (1ULL << componentTransform2D);
	parentObject->transformIndex = newTransform2D.poolIndex;

	newTransform2D.rotation = DEFAULT_ROTATION;
	newTransform2D.scale = defaultScale;

	transform2D_getPool()[*transform2D_getCounter()] = newTransform2D;
	*transform2D_getCounter() += 1;

	printf("Added new transform2D to object %zu \n", parentIndex);
	return newTransform2D.poolIndex;
}