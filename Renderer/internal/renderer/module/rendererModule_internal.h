#pragma once
#include "cOCT_EngineStructure.h"
#include "renderer/types_internal.h"

#include <glad/glad.h>

#define GL_CHECK() { GLenum err = glGetError(); if (err != GL_NO_ERROR) printf("GL error %d at line %d\n", err, __LINE__); }

struct iOCT_RENModule {
	cOCT_IDMap layerMap;
	cOCT_pool layerPool;

	GLuint spriteVBO;
	GLuint spriteEBO;
	GLuint spriteShader;

	GLuint texUniform;
};
extern iOCT_RENModule iOCT_RENModule_instance;

void iOCT_RENModule_init();
void iOCT_RENModule_free();