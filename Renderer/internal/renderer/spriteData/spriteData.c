#include "renderData.h"
#include "rendererObject/rendererObject.h"

#include "OCT_Math.h"
#include "types.h"
#include <glad/glad.h>

iOCT_renderData* iOCT_spriteInstances;
OCT_counter iOCT_spriteInstanceCapacity = iOCT_RENDEREROBJECT_DEFAULTMAX;

GLuint iOCT_renderData_initBuffer(int capacity) {
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, iOCT_RENDEREROBJECT_DEFAULTMAX * sizeof(iOCT_renderData), NULL, GL_DYNAMIC_DRAW);
	iOCT_spriteInstances =  glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	return iOCT_spriteInstances;
}