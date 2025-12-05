#include "rendererObject_internal.h"
#include "renderer/layer/layer_internal.h"
#include "shaders/shader/shader_internal.h"
static GLuint VAO_create() {
	GLuint newVAO = 0;
	glGenVertexArrays(1, &newVAO);    // create the array and buffers
	glBindVertexArray(newVAO);
	return newVAO;
}

static GLuint VBO_create(vertexPackage vertexInfo, bool dynamic) {
	GLuint newVBO = 0;
	glGenBuffers(1, &newVBO);
	glBindBuffer(GL_ARRAY_BUFFER, newVBO);

	if (dynamic) {
		glBufferData(GL_ARRAY_BUFFER, vertexInfo.vertexCount * vertexInfo.componentCount * sizeof(float), vertexInfo.vertexArray, GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, vertexInfo.vertexCount * vertexInfo.componentCount * sizeof(float), vertexInfo.vertexArray, GL_DYNAMIC_DRAW);
	}
	return newVBO;
}

static GLuint EBO_create(vertexPackage vertexInfo, bool dynamic) {
	GLuint newEBO = 0;
	glGenBuffers(1, &newEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newEBO);
	if (!dynamic) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexInfo.indexCount * sizeof(GLuint), vertexInfo.indexArray, GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexInfo.indexCount * sizeof(GLuint), vertexInfo.indexArray, GL_DYNAMIC_DRAW);
	}
	return newEBO;
}

static void vertexAttributes_set(vertexPackage vertexInfo) {
	glVertexAttribPointer(POSITION_INDEX, vertexInfo.componentCount, GL_FLOAT, GL_FALSE, vertexInfo.componentCount * sizeof(float), (void*)(POSITION_OFFSET * sizeof(float)));
	glEnableVertexAttribArray(POSITION_INDEX);
}

//static GLuint createMesh();

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
	
	// Debug hitboxes
	vertexPackage hitBoxInfo = packageVertices(gameObjectHandle, componentHitBox2D);		// package vertex and index data depending on componentType
	printf("vertexCount=%zu componentCount=%zu\n", hitBoxInfo.vertexCount, hitBoxInfo.componentCount);
	printf("First float in packageVertices: %f\n", ((float*)&hitBoxInfo)[0]);
	iOCT_rendererObject newRendererObject = { 0 };
	newRendererObject.gameObjectHandle = gameObjectHandle;		// link renderer object to ECS object
	iOCT_layer* layer = iOCT_layer_get(layerID);
	printf("\n\nFLOAT DATA %f %f %f\n\n", hitBoxInfo.vertexArray[0], hitBoxInfo.vertexArray[1], hitBoxInfo.vertexArray[2]);

	newRendererObject.debug_VAO = VAO_create();							// create and configure GL objects
	glBindVertexArray(newRendererObject.debug_VAO);
	newRendererObject.debug_VBO = VBO_create(hitBoxInfo, dynamic);
	if (hitBoxInfo.triangles) {
		newRendererObject.debug_EBO = EBO_create(hitBoxInfo, dynamic);
	}
	vertexAttributes_set(hitBoxInfo);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	printf("VBO DATA...\n\n");
	float test[6 * 2];
	glBindBuffer(GL_ARRAY_BUFFER, newRendererObject.debug_VBO);
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(test), test);

	printf("v0 = %f, %f\n", test[0], test[1]);

	printf("\nVBO DATA DONE\n\n");

	newRendererObject.shaderProgram = shaderProgram;

	OCT_counter* currentCounter = iOCT_rendererObject_getCounter(layerID);	// log new rendererObject
	newRendererObject.rendererObjectID = *currentCounter;
	iOCT_rendererObject_getPool(*currentCounter);
	*currentCounter += 1;
	layer->entityMap[gameObjectHandle.entitySetID][gameObjectHandle.entityID] = newRendererObject.rendererObjectID;

	printf("registered object %zu\n", newRendererObject.rendererObjectID);
	return newRendererObject.rendererObjectID;
}

void iOCT_render_debug(OCT_entityHandle entity, iOCT_layerID layer) {
	if (iOCT_layer_get(layer)->entityMap[entity.entitySetID] == iOCT_NO_RENDEREROBJECT || iOCT_layer_get(layer)->entityMap[entity.entityID] == iOCT_NO_RENDEREROBJECT) {
	}
	iOCT_rendererObject_new(entity, layer, shader_hitBox2D, true);
	printf("NO RENDEREROBJECT, CREATING NEW\n");

	iOCT_rendererObjectID rendererObjectID = iOCT_layer_get(layer)->entityMap[entity.entitySetID][entity.entityID];
	iOCT_rendererObject* objectToRender = iOCT_rendererObject_get(rendererObjectID, layer);
	printf("got renderer object %zu", rendererObjectID);
	glBindVertexArray(objectToRender->debug_VAO);
	glUseProgram(iOCT_shaderProgramList[shader_hitBox2D]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

