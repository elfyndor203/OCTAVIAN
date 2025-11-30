#pragma once
#include "standards/rendererStandards.h"
#include "ECS_Renderer_Input/typeInterpreter.h"

#define MAX_RENDEREROBJECTS 1024
#define OCT_ID_EBO_NONE 0

typedef struct rendererObject rendererObject;
typedef struct vertexPackage vertexPackage;

OCT_rendererObjectID OCT_rendererObject_new(size_t engineLink, OCT_componentTypes componentType, uint shaderProgram, bool dynamic);

void OCT_renderObject_TEST_ONLY(OCT_rendererObjectID objectToRender);

 