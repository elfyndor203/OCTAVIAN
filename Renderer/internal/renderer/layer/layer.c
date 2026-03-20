#include "layer_internal.h"
#include "renderer/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "_ECS_Output/_REN_include.h"
#include <glad/glad.h>

#include "renderer/module/rendererModule_internal.h"
#include "renderer/rendererObject/rendererObject.h"
#include "renderer/spriteData/spriteData_internal.h"


iOCT_layer* iOCT_layer_get(OCT_ID layerID) {
	OCT_index index = iOCT_IDMap_getIndex(&iOCT_RENModule_instance.layerMap, layerID);
	return (iOCT_layer*)iOCT_pool_access(&iOCT_RENModule_instance.layerPool, index);
}

OCT_ID iOCT_layer_open(bool dynamic, GLuint atlas) {
	OCT_index newIndex;
	OCT_ID newID;
	iOCT_layer* newLayer;

	// register layer
	newLayer = (iOCT_layer*)iOCT_pool_addEntry(&iOCT_RENModule_instance.layerPool, &newIndex);
	newID = iOCT_IDMap_register(&iOCT_RENModule_instance.layerMap, newIndex);

	// set defaults, init pool/map
	newLayer->layerID = newID;
	newLayer->IDMap = iOCT_IDMap_init(newID, iOCT_POOLSIZE_DEFAULT);
	newLayer->pool = iOCT_pool_init(newID, iOCT_POOLSIZE_DEFAULT, sizeof(iOCT_rendererObject));
	newLayer->dynamic = dynamic;
	newLayer->spriteTextureAtlas = atlas;
	
	// VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, iOCT_RENModule_instance.spriteVBO);
	glVertexAttribPointer(iOCT_attrib_position, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(iOCT_attrib_position);
	glVertexAttribPointer(iOCT_attrib_vertUV, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(iOCT_attrib_vertUV);

	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iOCT_RENModule_instance.spriteEBO);

	// spritebuffer
	glGenBuffers(1, &newLayer->spriteBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, newLayer->spriteBuffer);
	glBufferData(GL_ARRAY_BUFFER, iOCT_POOLSIZE_DEFAULT * sizeof(iOCT_spriteData), NULL, GL_DYNAMIC_DRAW);	// initial size
	newLayer->spriteBufferCapacity = iOCT_POOLSIZE_DEFAULT;

		// matrix
	glVertexAttribPointer(iOCT_attrib_transformCol0, 3, GL_FLOAT, GL_FALSE, sizeof(iOCT_spriteData), (void*)offsetof(iOCT_spriteData, transform.c0r0));
	glEnableVertexAttribArray(iOCT_attrib_transformCol0);
	glVertexAttribDivisor(iOCT_attrib_transformCol0, 1);

	glVertexAttribPointer(iOCT_attrib_transformCol1, 3, GL_FLOAT, GL_FALSE, sizeof(iOCT_spriteData), (void*)offsetof(iOCT_spriteData, transform.c1r0));
	glEnableVertexAttribArray(iOCT_attrib_transformCol1);
	glVertexAttribDivisor(iOCT_attrib_transformCol1, 1);

	glVertexAttribPointer(iOCT_attrib_transformCol2, 3, GL_FLOAT, GL_FALSE, sizeof(iOCT_spriteData), (void*)offsetof(iOCT_spriteData, transform.c2r0));
	glEnableVertexAttribArray(iOCT_attrib_transformCol2);
	glVertexAttribDivisor(iOCT_attrib_transformCol2, 1);

		// color
	glVertexAttribPointer(iOCT_attrib_color, 4, GL_FLOAT, GL_FALSE, sizeof(iOCT_spriteData), (void*)offsetof(iOCT_spriteData, color));
	glEnableVertexAttribArray(iOCT_attrib_color);
	glVertexAttribDivisor(iOCT_attrib_color, 1);

		// uv
	glVertexAttribPointer(iOCT_attrib_texUV, 4, GL_FLOAT, GL_FALSE, sizeof(iOCT_spriteData), (void*)offsetof(iOCT_spriteData, uvRect));
	glEnableVertexAttribArray(iOCT_attrib_texUV);
	glVertexAttribDivisor(iOCT_attrib_texUV, 1);

	newLayer->spriteVAO = VAO;
	return newID;
}

void iOCT_layer_close(iOCT_layer* layer) {
	iOCT_IDMap_free(&layer->IDMap);
	iOCT_pool_free(&layer->pool);
}

void iOCT_layer_draw(iOCT_layer* layer) {
	if (layer->dynamic == false) {
		return;
	}

	iOCT_rendererObject* array = (iOCT_rendererObject*)layer->pool.array;
	iOCT_rendererObject* renObj;

	glBindVertexArray(layer->spriteVAO);

	// shaders and textures
	glUseProgram(iOCT_RENModule_instance.spriteShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, layer->spriteTextureAtlas);
	glUniform1i(iOCT_RENModule_instance.texUniform, 0);

	// sprite instance buffer
	glBindBuffer(GL_ARRAY_BUFFER, layer->spriteBuffer);
	glBufferData(GL_ARRAY_BUFFER, layer->pool.count * sizeof(iOCT_spriteData), NULL, GL_DYNAMIC_DRAW);	// orphan
	iOCT_spriteData* buffer = (iOCT_spriteData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	iOCT_spriteData* slot;
	for (int i = 0; i < layer->pool.count; i++) {
		renObj = &array[i];
		slot = &buffer[i];

		slot->transform = _OCT_transform2D_getMatrix(renObj->transformHandle);
		slot->color = renObj->color;
		slot->uvRect = renObj->uvRect;
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);	

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, layer->pool.count);

	GL_CHECK();
}