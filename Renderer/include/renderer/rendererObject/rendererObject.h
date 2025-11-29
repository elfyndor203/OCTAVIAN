#pragma once
#include "standards/rendererStandards.h"

#define MAX_RENDEREROBJECTS 1024
#define OCT_ID_EBO_NONE 0

typedef struct rendererObject rendererObject;
typedef struct vertexPackage vertexPackage;

OCT_rendererObjectID OCT_rendererObject_new(size_t engineIndex, vertexPackage* vertexInfo, bool dynamic);

void OCT_TEST_RENDER_OBJECT(OCT_rendererObjectID objectToRender);

 