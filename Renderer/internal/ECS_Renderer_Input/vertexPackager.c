#include "ECS_Renderer_Input/vertexPackager_internal.h"

#include "mesh/box2D_internal.h"



vertexPackage packageVertices(OCT_entityHandle gameObjectHandle, OCT_componentTypes componentType) {
	vertexPackage newVertexPackage = { 0 };
	switch (componentType) {
		case componentHitBox2D:
			;
			OCT_rectangle2D box = REN_vertices_get(gameObjectHandle, componentType);

			newVertexPackage.componentCount = iOCT_MESH_BOX2D_COMPONENT_COUNT;
			newVertexPackage.vertexCount = iOCT_MESH_BOX2D_VERTEX_COUNT;
			newVertexPackage.vertexArray = ;
			newVertexPackage.indexArray = iOCT_rectangle2D_indices;
			newVertexPackage.indexCount = REN_HITBOX2D_INDEXCOUNT;
			newVertexPackage.triangles = REN_TRIANGES;
			printf("packaged hitbox2D info\n");
			break;
		default:
			OCT_logError(EXIT_NOT_YET_IMPLEMENTED);
	}
	return newVertexPackage;
}


