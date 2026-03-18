#include "layer_internal.h"
#include "renderer/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "_ECS_Output/_REN_include.h"
#include <glad/glad.h>

#include "renderer/module/rendererModule_internal.h"
#include "renderer/rendererObject/rendererObject.h"
#include "renderer/spriteData/spriteData_internal.h"

iOCT_layer* iOCT_layer_get(OCT_ID layerID) {
	OCT_index index = iOCT_IDMap_getIndex(&iOCT_RENModule_instance.IDMap, layerID);
	return (iOCT_layer*)iOCT_pool_access(&iOCT_RENModule_instance.IDMap, index);
}

OCT_ID iOCT_layer_open(bool dynamic) {
	OCT_index newIndex;
	OCT_ID newID;
	iOCT_layer* newLayer;

	// register layer
	newLayer = (iOCT_layer*)iOCT_pool_addEntry(&iOCT_RENModule_instance.pool, &newIndex);
	newID = iOCT_IDMap_register(&iOCT_RENModule_instance.IDMap, newIndex);

	// set defaults, init pool/map
	newLayer->layerID = newID;
	newLayer->IDMap = iOCT_IDMap_init(newID, OCT_POOLSIZE_DEFAULT);
	newLayer->pool = iOCT_pool_init(newID, OCT_POOLSIZE_DEFAULT, sizeof(iOCT_rendererObject));
	newLayer->dynamic = dynamic;
	
	// spritebuffer
	glGenBuffers(1, &newLayer->spriteBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, newLayer->spriteBuffer);
	glBufferData(GL_ARRAY_BUFFER, OCT_POOLSIZE_DEFAULT * sizeof(iOCT_spriteData), NULL, GL_DYNAMIC_DRAW);	// initial size
	newLayer->spriteCapacity = OCT_POOLSIZE_DEFAULT;

	// VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	note do vbo stuff in module, maybe get rid of module as a whole to store stuff or store the vbo in each renobj? probably not

		// matrix
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(iOCT_spriteData), (void*)offsetof(iOCT_spriteData, transform.r0c0));
	glEnableVertexAttribArray(0);
	glVertexAttribDivisor(0, 1);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(iOCT_spriteData), (void*)offsetof(iOCT_spriteData, transform.r1c0));
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(iOCT_spriteData), (void*)offsetof(iOCT_spriteData, transform.r2c0));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

		// color
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(iOCT_spriteData), (void*)offsetof(iOCT_spriteData, color));
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);

		// uv
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(iOCT_spriteData), (void*)offsetof(iOCT_spriteData, uvRect));
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);
	newLayer->VAO = VAO;

	return newID;
}

void iOCT_layer_draw(iOCT_layer* layer) {
	if (layer->dynamic == false) {
		return;
	}

	iOCT_rendererObject* array = (iOCT_rendererObject*)layer->pool.array;
	iOCT_rendererObject* renObj;

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
	glBindVertexArray(layer->VAO);
}