#pragma once
#include "renderer/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "Math.h"
#include <glad/glad.h>
#include <stdbool.h>

#include "renderer/rendererObject/rendererObject.h"

enum iOCT_attributes {
	iOCT_attrib_position = 0,
	iOCT_attrib_vertUV,
	iOCT_attrib_transformCol0,
	iOCT_attrib_transformCol1,
	iOCT_attrib_transformCol2,
	iOCT_attrib_color,
	iOCT_attrib_texUV
};

struct iOCT_layer {
	OCT_ID layerID;

	cOCT_IDMap IDMap;
	cOCT_pool pool;

	GLuint spriteVAO;

	GLuint spriteBuffer;
	OCT_counter spriteBufferCapacity;
	GLuint spriteTextureAtlas;

	bool dynamic;
};

iOCT_layer* iOCT_layer_get(OCT_ID layerID);

OCT_ID iOCT_layer_open(bool dynamic, GLuint atlas);
void iOCT_layer_close(iOCT_layer* context);
void iOCT_layer_draw(iOCT_layer* layer);
