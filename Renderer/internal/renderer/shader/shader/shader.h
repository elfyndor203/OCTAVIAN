#pragma once
#include <glad/glad.h>

GLuint iOCT_shader_load(char* path);
GLuint iOCT_shader_createProgram(char* vert, char* frag);