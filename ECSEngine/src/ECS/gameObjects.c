#include "ECS/gameObjects.h"

gameObject* createBlankGameObject() {
	gameObject* newGameObject = calloc(1, sizeof(gameObject));
	return newGameObject;
}

void addComponent(gameObject* parentObject, componentTypes componentType, void* componentToAdd) {	// adds an already created component to an object
	parentObject->componentsList[parentObject->componentsCountTotal] = componentToAdd;				// sets next available slot in componentsList to the new component's pointer
	parentObject->componentsCountTotal += 1;
	parentObject->componentsMask |= (1ULL << componentType);										// marks the component as visible
	parentObject->componentsCountPer[componentType] += 1;											// adds 1 to the counter for that component type	
}

gameObject* createGameObject(int componentsToAdd, ...) {
	va_list components;
	va_start(components, componentsToAdd);

	gameObject* newGameObject = createBlankGameObject();

	for (int i = 0; i < componentsToAdd; i++) {
		componentTypes currentComponent = va_arg(components, componentTypes);

		switch (currentComponent) {
		case componentChildObject:
			break;

		case componentPosition2D:
			;
			position2D* position2D = createDefaultPosition2D(newGameObject);
			addComponent(newGameObject, componentPosition2D, position2D);
			break;

		case componentTransform2D:
			break;

		case componentHitBox2D:
			;
			hitBox2D* hitBox2D = createDefaultHitBox2D(newGameObject);
			addComponent(newGameObject, componentHitBox2D, hitBox2D);
			break;
		default:
			printf("Unknown component type: %d\n", currentComponent);
			exit(EXIT_FAILURE);
		}
	}

	va_end(components);
	return newGameObject;
}

void printComponentsList(gameObject* parent) {
	printf("%d\n", parent->componentsCountTotal);
	printf("%" PRIu64 "\n", parent->componentsMask);
}







