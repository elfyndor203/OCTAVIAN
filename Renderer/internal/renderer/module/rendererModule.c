#include "rendererModule_internal.h"
#include "renderer/types_internal.h"

#include "cOCT_EngineStructure.h"
#include <glad/glad.h>

#include "renderer/layer/layer_internal.h"
#include "renderer/shader/shader/shader.h"

iOCT_RENModule iOCT_RENModule_instance = { 0 };


static const float iOCT_quadVerts[16] = {
	-0.5f, -0.5f,  0.0f, 0.0f,  // bottom left
	 0.5f, -0.5f,  1.0f, 0.0f,  // bottom right
	 0.5f,  0.5f,  1.0f, 1.0f,  // top right
	-0.5f,  0.5f,  0.0f, 1.0f   // top left
};

static const unsigned int iOCT_quadIndices[6] = {
	0, 1, 2,
	0, 2, 3
};

void iOCT_RENModule_init() {
	iOCT_RENModule_instance.layerMap = iOCT_IDMap_init(OCT_subsystem_renderer, iOCT_POOLSIZE_DEFAULT);
	iOCT_RENModule_instance.layerPool = iOCT_pool_init(OCT_subsystem_renderer, iOCT_POOLSIZE_DEFAULT, sizeof(iOCT_layer));

	glGenBuffers(1, &iOCT_RENModule_instance.spriteVBO);
	glBindBuffer(GL_ARRAY_BUFFER, iOCT_RENModule_instance.spriteVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(iOCT_quadVerts), &iOCT_quadVerts, GL_STATIC_DRAW);

	glGenBuffers(1, &iOCT_RENModule_instance.spriteEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iOCT_RENModule_instance.spriteEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iOCT_quadIndices), &iOCT_quadIndices, GL_STATIC_DRAW);

	iOCT_RENModule_instance.spriteShader = iOCT_shader_createProgram(
		"C:/Users/Elfyndor/MyDocuments/Projects/OCTAVIAN/Renderer/internal/renderer/shader/sprite/sprite.vert",
		"C:/Users/Elfyndor/MyDocuments/Projects/OCTAVIAN/Renderer/internal/renderer/shader/sprite/sprite.frag");

	iOCT_RENModule_instance.texUniform = glGetUniformLocation(iOCT_RENModule_instance.spriteShader, "tex");
	GL_CHECK();
}

void iOCT_RENModule_free() {
	iOCT_layer* array = (iOCT_layer*)iOCT_RENModule_instance.layerPool.array;

	for (int index = 0; index < iOCT_RENModule_instance.layerPool.count; index++) {
		iOCT_layer* layer = &array[index];
		iOCT_layer_close(layer);
	}
	iOCT_IDMap_free(&iOCT_RENModule_instance.layerMap);
	iOCT_pool_free(&iOCT_RENModule_instance.layerPool);
}