#pragma once
#include "rendererObject.h"

#define GLOBJECT_NEW(inputDataArray, inputDataCount) ((GLRequest){.ID = -1, .dataArray = inputDataArray, .dataCount = inputDataCount, .createNewID = true})				// for simpler use of GLRequest, -1 == create new
#define GLOBJECT_EXISTING(IDNum) ((GLRequest){.ID = (IDNum), .createNewID = false})
#define VAO_NEW GLOBJECT_NEW(0, 0)	// aliases
#define VBO_NEW(dataArray, dataCount) GLOBJECT_NEW(dataArray, dataCount)
#define EBO_NEW(dataArray, dataCount) GLOBJECT_NEW(dataArray, dataCount)
#define EBO_NONE GLOBJECT_EXISTING(0)											// when no EBO, createNEWID is false, but nothing will get bound

#define VAO_EXISTING(IDNum) GLOBJECT_EXISTING(IDNum)
#define VBO_EXISTING(IDNum) GLOBJECT_EXISTING(IDNum)
#define EBO_EXISTING(IDNum) GLOBJECT_EXISTING(IDNum)

#define ID_CREATE_NEW -1				// will never be an OpenGL ID
#define ID_EBO_NONE 0

typedef struct {
	int ID;
	size_t dataCount;
	void* dataArray;
	bool createNewID;
} GLRequest;				// for type protection between GLuint and creating a new ID using -1

rendererObjectIndex rendererObject_register(size_t engineIndex, GLRequest VAORequest, GLRequest VBORequest, GLRequest EBORequest, bool is3D, bool dynamic);

GLuint VAO_create();
GLuint VBO_create(GLsizeiptr vertexCount, float* dataArray, size_t dimensions, bool dynamic);
GLuint EBO_create(GLsizeiptr indexCount, uint* indexArray, bool dynamic);
void GLAttributes_set(GLuint VAO, GLuint VBO, size_t dimensions);