#include "gameObject_internal.h"

OCT_gameObjectHandle OCT_gameObject_createNew(OCT_gameObjectHandle parentObjectHandle) {
	iOCT_sceneID sceneID = parentObjectHandle.sceneID;
	iOCT_gameObjectID parentID = parentObjectHandle.gameObjectID;
	iOCT_gameObjectID newGameObjectID =  iOCT_gameObject_createNew(sceneID, parentID);
	iOCT_gameObjectHandle newHandle = { sceneID, newGameObjectID };
	return newHandle;
}

bool OCT_gameObject_hasComponent(OCT_gameObjectHandle gameObjectHandle, OCT_componentTypes component) {
	iOCT_sceneID sceneID = gameObjectHandle.sceneID;
	iOCT_gameObjectID gameObjectID = gameObjectHandle.gameObjectID;
	return iOCT_gameObject_hasComponent(sceneID, gameObjectID, component);
}