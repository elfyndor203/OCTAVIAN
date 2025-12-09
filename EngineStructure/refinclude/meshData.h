#pragma once
#include <stdint.h>
#include "OCT_Math.h"

#define iOCT_MAX_VERTICES_2D 64
#define iOCT_MAX_COMPONENTS_2D 8

typedef struct _OCT_meshData2D_simple {
	size_t vertexCount;
	float* vertexBuffer[iOCT_MAX_VERTICES_2D * iOCT_MAX_COMPONENTS_2D];
	size_t indexCount;
	int* indices;
} _OCT_meshData2D_simple;

_OCT_meshData2D_simple _OCT_meshData2D_simple_writeRectangle(OCT_rectangle2D rect);