#pragma once
#include "renderer/rendererObject/rendererObject.h"
#include "standards/rendererStandards_internal.h"

#define POSITION_INDEX 0
#define POSITION_OFFSET 0

typedef struct rendererObject {
	size_t engineLink;
	size_t poolIndex;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	GLuint shaderProgram;
} rendererObject;

typedef struct vertexPackage {
	size_t componentCount;
	size_t vertexCount;
	float* vertexArray;
	bool triangles;
	size_t indexCount;
	uint* indexArray;
} vertexPackage;

