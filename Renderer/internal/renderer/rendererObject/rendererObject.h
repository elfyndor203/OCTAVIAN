#pragma once
#include "standards/myStandards.h"

#define MAX_RENDEREROBJECTS 1024
#define CREATE_NEW_ID -1				// will never be an OpenGL ID
#define NO_EBO_USED 0

typedef struct {
	size_t engineLink;
	size_t poolIndex;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

} rendererObject;

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
