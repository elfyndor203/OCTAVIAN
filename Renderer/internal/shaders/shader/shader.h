#pragma once
#include "standards/myStandards.h"

unsigned int vertexShader_initialize(const char* vertexShader);
unsigned int fragmentShader_initialize(const char* fragmentShader);

unsigned int shaderProgram_create(int vertexShader, int fragmentShader);
