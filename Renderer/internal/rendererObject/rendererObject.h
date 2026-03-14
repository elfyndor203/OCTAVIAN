#pragma once
#include "OCT_EngineStructure.h"
#include "OCT_Math.h"

#include <glad/glad.h>

#define iOCT_RENDEREROBJECT_DEFAULTMAX 64

struct iOCT_rendererObject {
	GLuint mesh;
	GLuint texture;
	OCT_handle engineHandle;
	iOCT_renderData data;
};