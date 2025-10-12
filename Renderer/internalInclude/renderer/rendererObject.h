#pragma once
#include "myStandards.h"

#define NEW_GLOBJECT(dataArray, dataCount) ((GLRequest){.ID = -1, .dataArray = dataArray, .dataCount = dataCount, .createNewID = true})				// for simpler use of GLRequest, -1 == create new
#define EXISTING_GLOBJECT(IDNum) ((GLRequest){.ID = (IDNum), .createNewID = false})
#define NEW_VAO(dataArray, dataCount) NEW_GLOBJECT(dataArray, dataCount)	// aliases
#define NEW_VBO(dataArray, dataCount) NEW_GLOBJECT(dataArray, dataCount)
#define NEW_EBO(dataArray, dataCount) NEW_GLOBJECT(dataArray, dataCount)
#define NO_EBO EXISTING_GLOBJECT(0)											// when no EBO, createNEWID is false, but nothing will get bound
#define EXISTING_VAO(IDNum) EXISTING_GLOBJECT(IDNum)
#define EXISTING_VBO(IDNum) EXISTING_GLOBJECT(IDNum)
#define EXISTING_EBO(IDNum) EXISTING_GLOBJECT(IDNum)


#define MAX_RENDEREROBJECTS 1024
#define CREATE_NEW_ID -1
#define NO_EBO 0

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
	float* dataArray;
	bool createNewID;	
} GLRequest;				// for type protection between GLuint and creating a new ID using -1

void registerObject(size_t engineIndex, GLRequest VAORequest, GLRequest VBORequest, GLRequest EBORequest, bool is3D, bool dynamic);

GLuint createVAO();
GLuint createVBO(GLsizeiptr vertexCount, float* dataArray, size_t dimensions, bool dynamic);
GLuint createEBO(GLsizeiptr indexCount, uint* indexArray, bool dynamic);
void setGLAttributes(GLuint VAO, GLuint VBO, size_t dimensions);
