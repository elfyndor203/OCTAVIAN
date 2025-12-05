#include "hitBoxData_internal.h"

size_t* REN_hitBox2DVertices_getCount() {
	return iREN_hitBox2DVertices_getCount();
}
size_t* REN_hitBox2DIndices_getCount() {
	return iREN_hitBox2DIndices_getCount;
}

float* REN_hitBox2DVertices_get(OCT_entityHandle entityHandle) {
	iOCT_entitySetID entitySetID = entityHandle.entitySetID;
	iOCT_entityID entityID = entityHandle.entityID;
	return iREN_hitBox2DVertices_get(entitySetID, entityID);
}

unsigned int* REN_hitBox2DIndices_get() {
	return iREN_hitBox2DIndices_get();
}