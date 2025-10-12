#pragma once
#include "myStandards.h"

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

rendererObjectIndex registerObject(size_t engineIndex, GLRequest VAORequest, GLRequest VBORequest, GLRequest EBORequest, bool is3D, bool dynamic);

GLuint createVAO();
GLuint createVBO(GLsizeiptr vertexCount, float* dataArray, size_t dimensions, bool dynamic);
GLuint createEBO(GLsizeiptr indexCount, uint* indexArray, bool dynamic);
void setGLAttributes(GLuint VAO, GLuint VBO, size_t dimensions);
