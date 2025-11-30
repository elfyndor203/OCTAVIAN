#include "ECS_Renderer_Input/typeInterpreter_internal.h"

vertexPackage packageVertices(OCT_componentID engineLink, OCT_componentTypes componentType) {
	vertexPackage newVertexPackage = { 0 };
	switch (componentType) {
		case componentHitBox2D:
			newVertexPackage.componentCount = REN_HITBOX2D_COMPONENTCOUNT;
			newVertexPackage.vertexArray = REN_hitBox2DVertices_get(engineLink);
			newVertexPackage.vertexCount = REN_HITBOX2D_VERTEXCOUNT;
			newVertexPackage.indexArray = REN_hitBox2DIndices_get();
			newVertexPackage.indexCount = REN_HITBOX2D_INDEXCOUNT;
			newVertexPackage.triangles = REN_TRIANGES;
			break;
		default:
			OCT_logError(EXIT_NOT_YET_IMPLEMENTED);
	}
	return newVertexPackage;
}


