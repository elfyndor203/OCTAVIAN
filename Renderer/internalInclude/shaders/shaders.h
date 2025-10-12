#pragma once
#include "myStandards.h"

#include "shaders/shaders.h"

unsigned int initializeVertexShader(const char* vertexShader);
unsigned int initializeFragmentShader(const char* fragmentShader);

unsigned int createShaderProgram(int vertexShader, int fragmentShader);
