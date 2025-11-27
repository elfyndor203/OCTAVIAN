#include "rendererObject_internal.h"

#include "renderer/scene/scene.h"
#include "definitions/macros.h"

rendererObjectIndex rendererObject_register(size_t engineIndex, GLRequest VAORequest, GLRequest VBORequest, GLRequest EBORequest, bool is3D, bool dynamic) {	// determines whether or not to generate a new VAO
	rendererObject newRendererObject = { 0 };
	newRendererObject.engineLink = engineIndex;

	if (VAORequest.createNewID == true || VBORequest.createNewID == true || EBORequest.createNewID == true) {
		size_t dimensions = 3;
		if (is3D == false) {
			dimensions = 2;
		}
		newRendererObject.VAO = VAO_create();
		newRendererObject.VBO = VBO_create(VBORequest.dataCount, VBORequest.dataArray, dimensions, dynamic);
		newRendererObject.EBO = EBO_create(EBORequest.dataCount, EBORequest.dataArray, dynamic);
		GLAttributes_set(newRendererObject.VAO, newRendererObject.VBO, dimensions);
	}
	else {
		newRendererObject.VAO = VAORequest.ID;
		newRendererObject.VBO = VBORequest.ID; // use existing VBO WARNING NOTE: may cause an issue if VBO is changed, generate new always if changing
		if (EBORequest.createNewID == true) {
			newRendererObject.EBO = EBORequest.ID;	// is allowed to just not have an EBO
		}
		else {
			newRendererObject.EBO = 0;		// only happens if a new one isn't created and an existing one isn't used
		}
	}

	rendererObject_getPool()[*rendererObject_getCounter()] = newRendererObject;
	*rendererObject_getCounter() += 1;
	return newRendererObject.poolIndex;
}

GLuint VAO_create() {
	GLuint newVAO = 0;
	glGenVertexArrays(1, &newVAO);    // create the array and buffers
	glBindVertexArray(newVAO);
	return newVAO;
}

GLuint VBO_create(GLsizeiptr vertexCount, float* dataArray, size_t dimensions, bool dynamic) {

	GLuint newVBO = 0;
	glGenBuffers(1, &newVBO);
	glBindBuffer(GL_ARRAY_BUFFER, newVBO);
	if (dynamic) {
		glBufferData(GL_ARRAY_BUFFER, vertexCount * dimensions * sizeof(float), dataArray, GL_STATIC_DRAW);		// change this if i want to switch between 2d and 3d
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, vertexCount * dimensions * sizeof(float), dataArray, GL_DYNAMIC_DRAW);		// change this if i want to switch between 2d and 3d
	}
	return newVBO;
}

GLuint EBO_create(GLsizeiptr indexCount, uint* indexArray, bool dynamic) {
	GLuint newEBO = 0;
	glGenBuffers(1, &newEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newEBO);
	if (dynamic) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indexArray, GL_DYNAMIC_DRAW);
	}
	return newEBO;
}

void GLAttributes_set(GLuint VAO, GLuint VBO, size_t dimensions) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

rendererObjectIndex rendererObject_new(size_t engineIndex, float* vertexArray, size_t vertexCount, uint* indexArray, size_t indexCount, bool is3D, bool isDynamic) {	// makes it so macros are not needed externally
	if (indexArray != NULL) {
		rendererObjectIndex newRendererObject = rendererObject_register(engineIndex, VAO_NEW, VBO_NEW(vertexArray, vertexCount), EBO_NEW(indexArray, indexCount), is3D, isDynamic);
	}
	else {
		rendererObjectIndex newRendererObject = rendererObject_register(engineIndex, VAO_NEW, VBO_NEW(vertexArray, vertexCount), EBO_NONE, is3D, isDynamic);
	}
	
}

void rendererObject_update(rendererObjectIndex object) {
	rendererObject* object = rendererObject_get(object);

}