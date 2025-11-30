#include "hitBoxData_internal.h"

unsigned int* hitBox2D_indexArray[REN_HITBOX2D_INDEXCOUNT] = {
	0, 1, 2,
	2, 3, 4
};

size_t* iREN_hitBox2DVertices_getCount() {
	return HITBOX2D_OUTPUT_VERTEX_COUNT;
}
size_t* iREN_hitBox2DIndices_getCount() {
	return HITBOX2D_OUTPUT_INDEX_COUNT;
}

// extracts only the corner vertices needed for the renderer from the struct within the hitbox
float* iREN_hitBox2DVertices_get(iOCT_sceneID sceneID, iOCT_componentID engineLink) {	//	NOTE_POINT2D_IF_CHANGED
	iOCT_hitBox2D* hitBox = iOCT_hitBox2D_get(sceneID, engineLink);
	iOCT_hitBox2DVertices* vertices = &hitBox->boxVertices;

	hitBox2DVertexBuffer[0] = vertices->bottomLeft.x;
	hitBox2DVertexBuffer[1] = vertices->bottomLeft.y;
	hitBox2DVertexBuffer[2] = vertices->bottomRight.x;
	hitBox2DVertexBuffer[3] = vertices->bottomRight.y;
	hitBox2DVertexBuffer[4] = vertices->topRight.x;
	hitBox2DVertexBuffer[5] = vertices->topRight.y;
	hitBox2DVertexBuffer[6] = vertices->topLeft.x;
	hitBox2DVertexBuffer[7] = vertices->topLeft.y;

	return hitBox2DVertexBuffer;
}

unsigned int* iREN_hitBox2DIndices_get() {
	return &hitBox2D_indexArray;
}
