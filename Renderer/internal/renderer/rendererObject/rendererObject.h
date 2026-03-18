#pragma once
#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"

#include <glad/glad.h>

#define iOCT_RENDEREROBJECT_DEFAULTMAX 64

struct iOCT_rendererObject {
	GLuint mesh;
	GLuint texture;
	OCT_vec4 color;
	OCT_rect2 uvRect;

	OCT_handle engineHandle;
	OCT_handle transformHandle; // direct access
};