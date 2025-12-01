#pragma once
#include "ECS_Renderer_Input/typeInterpreter.h"
#include "standards/rendererStandards_internal.h"

typedef struct vertexPackage {
	size_t componentCount;
	size_t vertexCount;
	float* vertexArray;
	size_t indexCount;
	uint* indexArray;
	bool triangles;
} vertexPackage;

vertexPackage packageVertices(OCT_gameObjectHandle gameObjectHandle, OCT_componentTypes componentType);
