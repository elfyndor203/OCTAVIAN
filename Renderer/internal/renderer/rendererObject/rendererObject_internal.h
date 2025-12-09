#pragma once
#include "standards/rendererStandards_internal.h"

#include "OCT_Math.h"

#define iOCT_MAX_RENDEREROBJECTS 1024

#define iOCT_NO_RENDEREROBJECT GENERIC_FAIL

#define OCT_ID_EBO_NONE 0
#define POSITION_INDEX 0
#define POSITION_OFFSET 0

typedef size_t iOCT_layerID;
typedef size_t iOCT_rendererObjectID;

typedef struct iOCT_rendererObject {
	OCT_entityHandle entityHandle;
	OCT_componentTypes componentType;

	iOCT_rendererObjectID rendererObjectID;
	iOCT_layerID layerID;
	
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	size_t vertexCount;
	size_t indexCount;
	GLuint shaderProgram;
} iOCT_rendererObject;

iOCT_rendererObject* iOCT_rendererObject_get(iOCT_rendererObjectID rendererObjectID, iOCT_layerID layerID);
iOCT_rendererObject* iOCT_rendererObject_getPool(iOCT_layerID layerID);
OCT_counter* iOCT_rendererObject_getCounter(iOCT_layerID layerID);

iOCT_rendererObjectID iOCT_rendererObject_new(OCT_entityHandle entityHandle, iOCT_layerID layerID, OCT_componentTypes componentType, GLuint shaderProgram, bool dynamic);
void iOCT_render(iOCT_rendererObjectID rendererObjectID, iOCT_layerID layerID);