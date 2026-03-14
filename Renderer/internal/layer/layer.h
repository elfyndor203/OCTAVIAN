#pragma once
#include "OCT_EngineStructure.h"
#include "types_internal.h"

#include "rendererObject/rendererObject.h"

struct iOCT_layer {
	OCT_ID layerID;

	OCT_IDMap IDMap;
	OCT_pool renObjPool;

	GLuint spriteBuffer;
};