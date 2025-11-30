#include "hitBoxData_internal.h"

uint32_t hitBox2D_indexArray[REN_HITBOX2D_INDEXCOUNT] = {
	0, 1, 2,
	2, 3, 4
};

vertex2D* REN_hitBox2DVertices_get(OCT_componentID engineLink) {	//	NOTE_POINT2D_IF_CHANGED
	hitBox2DVertices* vertices = OCT_hitBox2DVertices_get(engineLink);
	vertex2D vertexArray[REN_HITBOX2D_VERTEXCOUNT] = { vertices->bottomLeft, vertices->bottomRight, vertices->topRight, vertices->topLeft };
	return vertexArray;
}

uint32_t* REN_hitBox2DIndices_get() {
	return &hitBox2D_indexArray;
}
