#include "shaders/shader/shader.h"
#include "shaders/shader/shader_internal.h"

#include "ECS/components/componentTypes/componentTypes.h"

#include "shaders/hitBox2D/hitBox2D_shaders.h"

unsigned int OCT_initializeShaders(OCT_componentTypes componentType) {
	unsigned int vertex = 0;
	unsigned int fragment = 0;

	switch (componentType) {
	case componentHitBox2D:
		vertex = vertexShader_initialize(hitBox2D_vertexShaderSource);
		fragment = fragmentShader_initialize(hitBox2D_fragmentShaderSource);
		break;
	default:
		printf("failed to initialize shaders\n");
	}
	return shaderProgram_create(vertex, fragment);
}