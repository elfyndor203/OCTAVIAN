#pragma once
#include "standards/rendererStandards.h"

#define MAX_RENDEREROBJECTS 1024
#define OCT_ID_EBO_NONE 0

typedef struct rendererObject rendererObject;
typedef struct GLRequest GLRequest;

OCT_rendererObjectID OCT_rendererObject_new(size_t engineIndex, float* vertexArray, size_t vertexCount, uint* indexArray, size_t indexCount, bool is3D, bool isDynamic);

void OCT_TEST_RENDER_OBJECT(OCT_rendererObjectID objectToRender);

 