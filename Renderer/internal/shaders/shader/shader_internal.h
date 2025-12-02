#pragma once
#include "standards/rendererStandards_internal.h"

GLuint vertexShader_initialize(const char* vertexShader);
GLuint fragmentShader_initialize(const char* fragmentShader);

GLuint shaderProgram_create(int vertexShader, int fragmentShader);
