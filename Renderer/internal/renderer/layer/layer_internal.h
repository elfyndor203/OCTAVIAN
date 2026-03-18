#pragma once
#include "renderer/types_internal.h"

#include "cOCT_EngineStructure.h"

#include "renderer/rendererObject/rendererObject.h"

struct iOCT_layer {
	OCT_ID layerID;

	OCT_IDMap IDMap;
	iOCT_pool pool;

	GLuint VAO;
	GLuint spriteBuffer;
	OCT_counter spriteCapacity;

	bool dynamic;
};

iOCT_layer* iOCT_layer_get(OCT_ID layerID);

OCT_ID iOCT_layer_open(bool dynamic);
void iOCT_layer_close(iOCT_layer* context);
