#pragma once
#include "standards/rendererStandards_internal.h"
#include "_ECS_Output/_REN_include.h"

typedef struct {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	size_t vertexCount;
	size_t indexCount;
} iOCT_glInfo;

iOCT_glInfo iOCT_generateBuffers(OCT_entityHandle entity, OCT_componentTypes componentType);
void iOCT_updateVertexBuffer(OCT_entityHandle entity, OCT_componentTypes componentType);