#pragma once
#include "standards/rendererStandards_internal.h"
#include "_ECS_Output/_REN_include.h"

typedef struct {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
} iOCT_glInfo;

iOCT_glInfo iOCT_generateBuffers_debug(OCT_entityHandle entity);