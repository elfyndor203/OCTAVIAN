#pragma once
#include "standards/rendererStandards_internal.h"
#include "OCT_ECS.h"
#include "ECS_Renderer_Output/REN_include.h"

typedef struct vertexPackage {
	size_t componentCount;
	size_t vertexCount;
	float* vertexArray;
	size_t indexCount;
	unsigned int* indexArray;
	bool triangles;
} vertexPackage;

vertexPackage packageVertices(OCT_entityHandle gameObjectHandle, OCT_componentTypes componentType);
