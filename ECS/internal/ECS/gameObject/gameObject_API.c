#include "gameObject_internal.h"

OCT_gameObjectID OCT_gameObject_createNew(OCT_sceneID sceneID, OCT_gameObjectID parentID) {
	return iOCT_gameObject_createNew(sceneID, parentID);
}

bool OCT_gameObject_hasComponent(OCT_sceneID sceneID, OCT_gameObjectID gameObjectID, componentTypes component) {
	return iOCT_gameObject_hasComponent(sceneID, gameObjectID, component);
}