#pragma once
#include "standards/rendererStandards.h"

#define MAX_RENDEREROBJECTS 1024

typedef struct {
	size_t engineLink;
	size_t poolIndex;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	GLuint shaderProgram;
} rendererObject;

rendererObjectIndex rendererObject_new(size_t engineIndex, float* vertexArray, size_t vertexCount, uint* indexArray, size_t indexCount, bool is3D, bool isDynamic);

 