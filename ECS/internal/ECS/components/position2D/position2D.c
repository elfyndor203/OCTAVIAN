#include "position2D_internal.h"

#include "ECS/gameObject/gameObject_internal.h"
#include "ECS/scene/scene_internal.h"

vector2D defaultPosition2D = { DEFAULT_POSITION_X, DEFAULT_POSITION_Y };

componentIndex position2D_addNew(gameObjectIndex parentIndex) {								// attaches a new default position2D to some gameObject
	if (gameObject_hasComponent(parentIndex, componentPosition2D)) {
		logError(WARNING_COMPONENT_REPLACED);
	}

	gameObject* parentObject = gameObject_get(parentIndex);

	position2D newPosition2D = { 0 };							
	newPosition2D.poolIndex = *position2D_getCounter();						// it can find itself
	newPosition2D.parentIndex = parentIndex;								// it can find its parent object

	parentObject->componentsMask |= (1ULL << componentPosition2D);			// parent object knows it exists
	parentObject->positionIndex = newPosition2D.poolIndex;					// parent object can find it

	newPosition2D.globalPosition2D = defaultPosition2D;						// default values
	newPosition2D.localPosition2D = defaultPosition2D;

	position2D_getPool()[*position2D_getCounter()] = newPosition2D;			// add it to the pool
	*position2D_getCounter() += 1;

	printf("Added new position2D to object %zu \n", parentIndex);
	return newPosition2D.poolIndex;
}

componentIndex OCT_position2D_addNew(gameObjectIndex parentIndex) {
	return position2D_addNew(parentIndex);
}
