#include "ECS/gameObjects.h"
#include "ECS/componentPools.h"

size_t createGameObject(size_t parentIndex, bool is3D) {
	gameObject newGameObject = { 0 };
	
	if (is3D) {
		exit(EXIT_3D_NOT_SUPPORTED);										// change this later
	}
	else {
		newGameObject.poolIndex = gameObjectsCounter;						
		newGameObject.parentIndex = parentIndex;
		
		newGameObject.positionIndex = addNewPosition2D(newGameObject.poolIndex);					// stores the index of its position component
		newGameObject.componentsMask |= (1ULL << componentPosition2D);		// marks the gameObject as having a position component
	}

	gameObjectsPool[gameObjectsCounter] = newGameObject;					// stores gameObject in the next avail slot of the pool
	gameObjectsCounter += 1;

	return newGameObject.poolIndex;
}

void addComponentToGameObject(size_t parentIndex, componentTypes componentType) {
	gameObject* parentObject = &gameObjectsPool[parentIndex];

	switch (componentType) {
		case componentPosition2D: {
			parentObject->positionIndex = addNewPosition2D(parentIndex);
			break;
		}

		case componentTransform2D: {
			parentObject->transformIndex = addNewTransform2D(parentIndex);
			break;
		}

		case componentHitBox2D: {
			parentObject->hitBoxIndex = addNewHitBox2D(parentIndex);
			break;
		}

		case componentChildObject: {
			size_t newChildObject = createGameObject(parentIndex, false);		// creates a default childObject
			break;
		}	
	}
	parentObject->componentsMask |= (1ULL << componentType);
}

//gameObject* createGameObject(int componentsToAdd, ...) {
//	va_list components;
//	va_start(components, componentsToAdd);
//
//	gameObject* newGameObject = createGameObject();
//
//	for (int i = 0; i < componentsToAdd; i++) {
//		componentTypes currentComponent = va_arg(components, componentTypes);
//
//		switch (currentComponent) {
//		case componentChildObject:
//			break;
//
//		case componentPosition2D:
//			;
//			position2D* position2D = createDefaultPosition2D(newGameObject);
//			addComponent(newGameObject, componentPosition2D, position2D);
//			break;
//
//		case componentTransform2D:
//			break;
//
//		case componentHitBox2D:
//			;
//			hitBox2D* hitBox2D = createDefaultHitBox2D(newGameObject);
//			addComponent(newGameObject, componentHitBox2D, hitBox2D);
//			break;
//		default:
//			printf("Unknown component type: %d\n", currentComponent);
//			exit(EXIT_FAILURE);
//		}
//	}
//
//	va_end(components);
//	return newGameObject;
//}

//void printComponentsList(gameObject* parent) {
//	printf("%d\n", parent->componentsCountTotal);
//	printf("%" PRIu64 "\n", parent->componentsMask);
//}







