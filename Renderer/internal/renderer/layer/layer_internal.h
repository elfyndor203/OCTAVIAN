#pragma once
#include "renderer/types_internal.h"

#include "OCT_EngineStructure.h"

#include "renderer/rendererObject/rendererObject.h"

struct iOCT_layer {
	OCT_ID layerID;

	OCT_IDMap IDMap;
	OCT_pool renObjPool;

	GLuint spriteBuffer;
	OCT_counter spriteCapacity;
};

iOCT_layer iOCT_layer_get(OCT_ID layerID);

OCT_ID iOCT_layer_open();
void iOCT_layer_close(iOCT_layer* context);
