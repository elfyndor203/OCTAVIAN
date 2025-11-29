#include "rendererObject_internal.h"
#include "renderer/scene/scene_internal.h"

OCT_rendererObjectID OCT_rendererObject_new(size_t engineIndex, vertexPackage* vertexInfo, bool dynamic) {
	rendererObject newRendererObject = { 0 };
	newRendererObject.engineLink = engineIndex;

	newRendererObject.VAO = VAO_create();
	newRendererObject.VBO = VBO_create(vertexInfo, dynamic);
	if (!vertexInfo->triangles) {
		newRendererObject.EBO = EBO_create(vertexInfo, dynamic);
	}
	attributes_set(vertexInfo);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	counter* currentCounter = rendererObject_getCounter();
	newRendererObject.poolIndex = *currentCounter;
	rendererObject_getPool(*currentCounter);
	*currentCounter += 1;
}

static GLuint VAO_create() {
	GLuint newVAO = 0;
	glGenVertexArrays(1, &newVAO);    // create the array and buffers
	glBindVertexArray(newVAO);
	return newVAO;
}

static GLuint VBO_create(vertexPackage* vertexInfo, bool dynamic) {
	GLuint newVBO = 0;
	glGenBuffers(1, &newVBO);
	glBindBuffer(GL_ARRAY_BUFFER, newVBO);

	if (dynamic) {
		glBufferData(GL_ARRAY_BUFFER, vertexInfo->vertexCount * vertexInfo->componentCount * sizeof(float), vertexInfo->vertexArray, GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, vertexInfo->vertexCount * vertexInfo->componentCount * sizeof(float), vertexInfo->vertexArray, GL_DYNAMIC_DRAW);
	}
	return newVBO;
}

static GLuint EBO_create(vertexPackage* vertexInfo, bool dynamic) {
	GLuint newEBO = 0;
	glGenBuffers(1, &newEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newEBO);
	if (dynamic) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexInfo->indexCount * sizeof(GLuint), vertexInfo->indexArray, GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexInfo->indexCount * sizeof(GLuint), vertexInfo->indexArray, GL_DYNAMIC_DRAW);
	}
	return newEBO;
}

static void attributes_set(vertexPackage* vertexInfo) {
	glVertexAttribPointer(POSITION_INDEX, vertexInfo->componentCount, GL_FLOAT, GL_FALSE, vertexInfo->componentCount * vertexInfo->indexCount * sizeof(float), (void*)(POSITION_OFFSET * sizeof(float)));
}

static vertexPackage packageVertices(size_t componentCount, size_t vertexCount, float* vertexArray, bool triangles, size_t indexCount, uint* indexArray) {
	vertexPackage newVertexPackage = { 0 };
	newVertexPackage.componentCount = (GLsizeiptr)(componentCount);
	newVertexPackage.vertexCount = (GLsizeiptr)(vertexCount);
	newVertexPackage.vertexArray = (GLfloat*)(vertexArray);
	newVertexPackage.indexCount = (GLsizeiptr)(indexCount);
	newVertexPackage.indexArray = (GLuint*)(indexArray);
}