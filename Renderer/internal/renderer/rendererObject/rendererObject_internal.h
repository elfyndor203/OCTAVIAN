#pragma once
#include "renderer/rendererObject/rendererObject.h"
#include "standards/rendererStandards_internal.h"

#include "ECS_Renderer_Input/typeInterpreter_internal.h"

#define POSITION_INDEX 0
#define POSITION_OFFSET 0

typedef struct rendererObject {
	OCT_gameObjectHandle gameObjectHandle;
	OCT_rendererObjectID rendererObjectID;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	GLuint shaderProgram;
} rendererObject;
