#pragma once
#include "standards/rendererStandards_internal.h"

typedef enum iOCT_shaderTypes {
	shader_debug
};

#define iOCT_SHADER_DEFAULT_MAX 64

GLuint iOCT_shaderProgramList[iOCT_SHADER_DEFAULT_MAX];

GLuint* iOCT_initializeShaders();
