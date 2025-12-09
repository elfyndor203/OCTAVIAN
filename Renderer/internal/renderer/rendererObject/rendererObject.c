#include "rendererObject_internal.h"
#include "renderer/layer/layer_internal.h"
#include "shaders/shader/shader_internal.h"
#include "_REN_Input/bufferGeneration_internal.h"

iOCT_rendererObject* iOCT_rendererObject_get(iOCT_rendererObjectID rendererObjectID, iOCT_layerID layerID) {
	if (iOCT_layer_get(layerID) == iOCT_GET_FAILED || layerID > iOCT_layer_get(layerID)->rendererObjectCounter) {
		OCT_logError(ERR_RENDEREROBJECT_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	//printf("Got rendererObject #%zu from layer #%zu\n", rendererObjectID, layerID);
	return &iOCT_layer_get(layerID)->rendererObjectPool[rendererObjectID];	// access the layer, access the rendererObject, and return its pointer
}


iOCT_rendererObject* iOCT_rendererObject_getPool(iOCT_layerID layerID) {
	if (iOCT_layer_get(layerID) == iOCT_GET_FAILED) {
		OCT_logError(ERR_RENDEREROBJECTPOOL_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	//printf("Got rendererObjectPool from layer #%zu\n", layerID);
	return &iOCT_layer_get(layerID)->rendererObjectPool;
}

OCT_counter* iOCT_rendererObject_getCounter(iOCT_layerID layerID) {
	if (iOCT_layer_get(layerID) == iOCT_GET_FAILED) {
		OCT_logError(ERR_RENDEREROBJECTCOUNTER_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	//printf("Got rendererObjectCounter from layer #%zu\n", layerID);
	return &iOCT_layer_get(layerID)->rendererObjectCounter;
}

iOCT_rendererObjectID iOCT_rendererObject_new(OCT_entityHandle entityHandle, iOCT_layerID layerID, OCT_componentTypes componentType, GLuint shaderProgram, bool dynamic) {
	iOCT_rendererObject newRendererObject = { 0 };
	iOCT_glInfo buffers = iOCT_generateBuffers(entityHandle, componentType);
	newRendererObject.entityHandle = entityHandle;		// link renderer object to ECS object
	newRendererObject.componentType = componentType;
	// newRendererObject.rendererObjectID stored during registration
	newRendererObject.layerID = layerID;
	newRendererObject.VAO = buffers.VAO;
	newRendererObject.VBO = buffers.VBO;
	newRendererObject.EBO = buffers.EBO;
	newRendererObject.vertexCount = buffers.vertexCount;
	newRendererObject.indexCount = buffers.indexCount;
	printf("INDEX COUNT SET HERE TO %zu", newRendererObject.indexCount);

	newRendererObject.shaderProgram = shaderProgram;

	iOCT_layer* layer = iOCT_layer_get(layerID);								// register new rendererObject in layer
	OCT_counter* currentCounter = iOCT_rendererObject_getCounter(layerID);	
	newRendererObject.rendererObjectID = *currentCounter;
	iOCT_rendererObject_getPool(layerID)[*currentCounter] = newRendererObject;
	*currentCounter += 1;

	iOCT_rendererObjectHandle handle = { newRendererObject.rendererObjectID, newRendererObject.layerID };	// store in map
	iOCT_rendererObjectMap[entityHandle.entitySetID][entityHandle.entityID][componentType] = handle;

	printf("registered renderer object %zu\n", newRendererObject.rendererObjectID);
	return newRendererObject.rendererObjectID;
}

void iOCT_render(iOCT_rendererObjectID rendererObjectID, iOCT_layerID layerID) {
	iOCT_rendererObject* object = iOCT_rendererObject_get(rendererObjectID, layerID);
	//printf("Rendering rendererObject #%zu\n", rendererObjectID);

	glClearColor(0.1f, 0.2f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(object->VAO);
	glUseProgram(object->shaderProgram);
	printf("Index count = %zu\n", object->indexCount);
	glDrawElements(GL_TRIANGLES, object->indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

