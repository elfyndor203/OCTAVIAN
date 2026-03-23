#include "RENModule_internal.h"
#include "renderer/types_internal.h"

#include "cOCT_EngineStructure.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

#include "renderer/layer/layer_internal.h"
#include "renderer/shader/shader/shader_internal.h"

static OCT_mat3 iOCT_calcWorldProj(OCT_vec2 coordinateScale);

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

void OCT_RENModule_init(OCT_vec2 scale) {
	// check init order
	iOCT_RENModule_init(scale);
}
void iOCT_RENModule_init(OCT_vec2 coordinateScale) {
	iOCT_RENModule_instance.layerMap = cOCT_IDMap_init(OCT_subsystem_renderer, iOCT_POOLSIZE_DEFAULT);
	iOCT_RENModule_instance.layerPool = cOCT_pool_init(OCT_subsystem_renderer, iOCT_POOLSIZE_DEFAULT, sizeof(iOCT_layer));
	iOCT_RENModule_instance.textureCapacity = iOCT_TEXTURE_INITIALCAPACITY;
	iOCT_RENModule_instance.textureList = malloc(iOCT_TEXTURE_INITIALCAPACITY * sizeof(GLuint));

	glGenBuffers(1, &iOCT_RENModule_instance.spriteVBO);
	glBindBuffer(GL_ARRAY_BUFFER, iOCT_RENModule_instance.spriteVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(iOCT_quadVerts), &iOCT_quadVerts, GL_STATIC_DRAW);

	glGenBuffers(1, &iOCT_RENModule_instance.spriteEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iOCT_RENModule_instance.spriteEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iOCT_quadIndices), &iOCT_quadIndices, GL_STATIC_DRAW);

	// load basic sprite shader
	GLuint basicShader = iOCT_shader_createProgram(
		"../renderer/internal/renderer/shader/sprite/sprite.vert",
		"../renderer/internal/renderer/shader/sprite/sprite.frag");
	iOCT_RENModule_instance.spriteShader = basicShader;
	glUseProgram(basicShader);

	iOCT_RENModule_instance.worldScale = coordinateScale;
	iOCT_RENModule_instance.worldProj = iOCT_calcWorldProj(coordinateScale);
	iOCT_RENModule_instance.worldProjUniform = glGetUniformLocation(basicShader, "worldProj");
	glUniformMatrix3fv(iOCT_RENModule_instance.worldProjUniform, 1, GL_FALSE, &iOCT_RENModule_instance.worldProj.c0r0);
	GL_CHECK();
}

void iOCT_RENModule_free() {
	iOCT_layer* array = (iOCT_layer*)iOCT_RENModule_instance.layerPool.array;

	for (int index = 0; index < iOCT_RENModule_instance.layerPool.count; index++) {
		iOCT_layer* layer = &array[index];
		iOCT_layer_close(layer);
	}
	cOCT_IDMap_free(&iOCT_RENModule_instance.layerMap);
	cOCT_pool_free(&iOCT_RENModule_instance.layerPool);
	free(iOCT_RENModule_instance.textureList);
}

/// <summary>
/// Handle all incoming messages. Required between loading a texture and opening a layer.
/// </summary>
void OCT_RENModule_flush() {
	iOCT_RENModule_handleMSGs();
}
void OCT_RENModule_update() {
	// check update order
	iOCT_RENModule_update();
}
void iOCT_RENModule_update() {
	iOCT_RENModule_handleMSGs();

	iOCT_layer* array = (iOCT_layer*)iOCT_RENModule_instance.layerPool.array;
	iOCT_layer* layer;
	for (int i = 0; i < iOCT_RENModule_instance.layerPool.count; i++) {
		layer = &array[i];
		iOCT_layer_draw(layer);
	}

}

#pragma region helpers
static OCT_mat3 iOCT_calcWorldProj(OCT_vec2 coordinateScale) {
	OCT_mat3 proj = { 0 };
	proj.c0r0 = 2 / coordinateScale.x;
	proj.c1r1 = 2 / coordinateScale.y;
	proj.c2r0 = -1;
	proj.c2r1 = -1;
	proj.c2r2 = 1;
	return proj;
}
#pragma regionend

#pragma region cross-module requests
OCT_vec2 _OCT_worldRatio_get() {
	return iOCT_RENModule_instance.worldScale;
}
#pragma endregion