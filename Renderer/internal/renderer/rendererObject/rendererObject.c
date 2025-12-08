#include "rendererObject_internal.h"
#include "renderer/layer/layer_internal.h"
#include "shaders/shader/shader_internal.h"
#include "_REN_Input/bufferGeneration_internal.h"

iOCT_rendererObject* iOCT_rendererObject_get(iOCT_rendererObjectID rendererObjectID, iOCT_layerID layerID) {
	if (iOCT_layer_get(layerID) == iOCT_GET_FAILED || layerID > iOCT_layer_get(layerID)->rendererObjectCounter) {
		OCT_logError(ERR_RENDEREROBJECT_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	printf("Got rendererObject #%zu from layer #%zu\n", rendererObjectID, layerID);
	return &iOCT_layer_get(layerID)->rendererObjectPool[rendererObjectID];	// access the layer, access the rendererObject, and return its pointer
}

iOCT_rendererObject* iOCT_rendererObject_getPool(iOCT_layerID layerID) {
	if (iOCT_layer_get(layerID) == iOCT_GET_FAILED) {
		OCT_logError(ERR_RENDEREROBJECTPOOL_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	printf("Got rendererObjectPool from layer #%zu\n", layerID);
	return &iOCT_layer_get(layerID)->rendererObjectPool;
}

OCT_counter* iOCT_rendererObject_getCounter(iOCT_layerID layerID) {
	if (iOCT_layer_get(layerID) == iOCT_GET_FAILED) {
		OCT_logError(ERR_RENDEREROBJECTCOUNTER_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	printf("Got rendererObjectCounter from layer #%zu\n", layerID);
	return &iOCT_layer_get(layerID)->rendererObjectCounter;
}

iOCT_rendererObjectID iOCT_rendererObject_new(OCT_entityHandle gameObjectHandle, iOCT_layerID layerID, GLuint shaderProgram, bool dynamic) {
	
	iOCT_rendererObject newRendererObject = { 0 };
	newRendererObject.gameObjectHandle = gameObjectHandle;		// link renderer object to ECS object

	iOCT_layer* layer = iOCT_layer_get(layerID);
	newRendererObject.shaderProgram = shaderProgram;

	OCT_counter* currentCounter = iOCT_rendererObject_getCounter(layerID);	// log new rendererObject
	newRendererObject.rendererObjectID = *currentCounter;
	iOCT_rendererObject_getPool(*currentCounter);
	*currentCounter += 1;

	printf("registered object %zu\n", newRendererObject.rendererObjectID);
	return newRendererObject.rendererObjectID;
}

void iOCT_render_debug(OCT_entityHandle entity, iOCT_layerID layer) {
	iOCT_rendererObject* rendererObject;
	if (iOCT_rendererObject_get(entity.rendererObjectID, entity.layerID) == iOCT_GET_FAILED) {	//NOTE_MESSY??
		printf("NO RENDEREROBJECT, CREATING NEW\n");
		rendererObject = iOCT_rendererObject_get(iOCT_rendererObject_new(entity, layer, iOCT_shaderProgramList[shader_debug], true), layer); //NOTE_CHANGE_LATER TO SUPPORT OTHER SHADERS
		iOCT_generateBuffers_debug(entity);
	}
	else {
		rendererObject = iOCT_rendererObject_get(entity.rendererObjectID, entity.layerID);
		// NOTE_WRITE_UPDATE_HERE
	}

	glBindVertexArray(rendererObject->debug_VAO);
	glUseProgram(iOCT_shaderProgramList[shader_debug]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

