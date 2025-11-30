#include "rendererObject_internal.h"
#include "renderer/scene/scene_internal.h"

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
	if (dynamic) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexInfo.indexCount * sizeof(GLuint), vertexInfo.indexArray, GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexInfo.indexCount * sizeof(GLuint), vertexInfo.indexArray, GL_DYNAMIC_DRAW);
	}
	return newEBO;
}

static void vertexAttributes_set(vertexPackage vertexInfo) {
	glVertexAttribPointer(POSITION_INDEX, vertexInfo.componentCount, GL_FLOAT, GL_FALSE, vertexInfo.componentCount * sizeof(float), (void*)(POSITION_OFFSET * sizeof(float)));
}

OCT_rendererObjectID OCT_rendererObject_new(size_t engineLink, OCT_componentTypes componentType, uint shaderProgram, bool dynamic) {
	vertexPackage vertexInfo = packageVertices(engineLink, componentType);		// package vertex and index data depending on componentType
	rendererObject newRendererObject = { 0 };
	newRendererObject.engineLink = engineLink;		// link renderer object to ECS object

	newRendererObject.VAO = VAO_create();							// create and configure GL objects
	newRendererObject.VBO = VBO_create(vertexInfo, dynamic);
	if (vertexInfo.triangles) {
		newRendererObject.EBO = EBO_create(vertexInfo, dynamic);
	}
	vertexAttributes_set(vertexInfo);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	newRendererObject.shaderProgram = shaderProgram;

	counter* currentCounter = rendererObject_getCounter();	// log new rendererObject
	newRendererObject.poolIndex = *currentCounter;
	rendererObject_getPool(*currentCounter);
	*currentCounter += 1;
	printf("registered object %zu\n", newRendererObject.poolIndex);
	return newRendererObject.poolIndex;
}

void OCT_renderObject_TEST_ONLY(OCT_rendererObjectID objectToRender) {
	rendererObject* object = rendererObject_get(objectToRender);
	printf("got renderer object %zu", objectToRender);
	glBindVertexArray(object->VAO);
	glUseProgram(object->shaderProgram);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

