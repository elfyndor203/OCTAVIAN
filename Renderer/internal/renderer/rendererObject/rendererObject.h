#pragma once
#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"

#include <glad/glad.h>

#include "renderer/layer/layer_internal.h"

#define iOCT_RENDEREROBJECT_DEFAULTMAX 64

struct iOCT_rendererObject {
	//GLuint mesh;
	//GLuint texture;
	OCT_vec4 color;
	OCT_vec4 uvRect;

	OCT_handle engineHandle;
	OCT_handle transformHandle; // direct access
};

OCT_handle iOCT_rendererObject_add(iOCT_layer* layer, OCT_handle engineHandle, OCT_handle transform);