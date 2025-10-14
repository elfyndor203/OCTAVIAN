#pragma once
#include "myStandards.h"

#include "shaders/hitBoxShaders.h"

#include "layers.h"

int success;
char infoLog[512];

GLFWwindow* initializeWindow(char* windowName);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

unsigned int initializeVertexShader(char* vertexShader);
unsigned int initializeFragmentShader(char* vertexShader);
unsigned int createShaderProgram(int vertexShader, int fragmentShader);

unsigned int createVertexBuffer(float* layer, unsigned int vertexCount);
