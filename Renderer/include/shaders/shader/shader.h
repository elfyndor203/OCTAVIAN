#pragma once
#include "standards/rendererStandards.h"

unsigned int OCT_vertexShader_initialize(const char* vertexShader);
unsigned int OCT_fragmentShader_initialize(const char* fragmentShader);

unsigned int OCT_shaderProgram_create(int vertexShader, int fragmentShader);
