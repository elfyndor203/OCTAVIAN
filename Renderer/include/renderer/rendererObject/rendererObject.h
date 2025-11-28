#pragma once
#include "standards/rendererStandards.h"

#define MAX_RENDEREROBJECTS 1024

typedef struct rendererObject rendererObject;
typedef struct GLRequest GLRequest;

rendererObjectIndex OCT_rendererObject_new(size_t engineIndex, float* vertexArray, size_t vertexCount, uint* indexArray, size_t indexCount, bool is3D, bool isDynamic);

 