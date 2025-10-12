#include "renderer/rendererObject.h"
#include "renderer/scenes.h"
#include "definitions/macros.h"

size_t registerObject(size_t engineIndex, GLRequest VAORequest, GLRequest VBORequest, GLRequest EBORequest, bool is3D, bool dynamic) {	// determines whether or not to generate a new VBO, EBO, and VAO
	rendererObject newRendererObject = { 0 };
	newRendererObject.engineLink = engineIndex;

	if (VAORequest.createNewID == true || VBORequest.createNewID == true || EBORequest.createNewID == true) {
		size_t dimensions = 3;
		if (is3D == false) {
			dimensions = 2;
		}
		newRendererObject.VAO = createVAO();
		newRendererObject.VBO = createVBO(VBORequest.dataCount, VBORequest.dataArray, dimensions, dynamic);
		newRendererObject.EBO = createEBO(EBORequest.dataCount, EBORequest.dataArray, dynamic);
		setGLAttributes(newRendererObject.VAO, newRendererObject.VBO, dimensions);
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

	getRendererObjectPool()[*getRendererObjectCounter()] = newRendererObject;
	*getRendererObjectCounter() += 1;
	return newRendererObject.poolIndex;
}

GLuint createVAO() {
	GLuint newVAO = 0;
	glGenVertexArrays(1, &newVAO);    // create the array and buffers
	glBindVertexArray(newVAO);
	return newVAO;
}

GLuint createVBO(GLsizeiptr vertexCount, float* dataArray, size_t dimensions, bool dynamic) {

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

GLuint createEBO(GLsizeiptr indexCount, uint* indexArray, bool dynamic) {
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

void setGLAttributes(GLuint VAO, GLuint VBO, size_t dimensions) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
