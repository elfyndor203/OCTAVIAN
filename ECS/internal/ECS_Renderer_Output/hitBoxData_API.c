#include "hitBoxData_internal.h"

size_t* REN_hitBox2DVertices_getCount() {
	return iREN_hitBox2DVertices_getCount();
}
size_t* REN_hitBox2DIndices_getCount() {
	return iREN_hitBox2DIndices_getCount;
}

float* REN_hitBox2DVertices_get(OCT_gameObjectHandle gameObjectHandle) {
	iOCT_sceneID sceneID = gameObjectHandle.sceneID;
	iOCT_gameObjectID gameObjectID = gameObjectHandle.gameObjectID;
	return iREN_hitBox2DVertices_get(sceneID, gameObjectID);
}

unsigned int* REN_hitBox2DIndices_get() {
	return iREN_hitBox2DIndices_get();
}