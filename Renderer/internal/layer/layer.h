#pragma once
#include "OCT_EngineStructure.h"
#include "types.h"

#include "rendererObject/rendererObject.h"

struct iOCT_layer {
	OCT_ID layerID;

	iOCT_rendererObject* renObjPool;
	OCT_counter renObjCount;

	GLuint spriteBuffer;
	GLuint particleBuffer;
	GLuint shapeBuffer;
};