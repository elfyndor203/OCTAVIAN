#include "bufferGeneration_internal.h"
#include "_ECS_Output/_REN_include.h"

#include "mesh/prototypes.h"
#include "shaders/shader/shader_internal.h"
#include "renderer/rendererObject/rendererObject_internal.h"
#include "renderer/layer/layer_internal.h"

const GLsizei debugStride = 0;

iOCT_glInfo iOCT_generateBuffers_debug(OCT_entityHandle entity) {	// generates buffers for a new rendererObject
	OCT_rectangle2D hitBox = _REN_vertices_getDebug(entity);

	float vertices[OCT_RECTANGLE2D_VERTEXCOUNT * 2] = {
		hitBox.bottomLeft.x, hitBox.bottomLeft.y,
		hitBox.bottomRight.x, hitBox.bottomRight.y,
		hitBox.topRight.x, hitBox.topRight.y,
		hitBox.topLeft.x, hitBox.topLeft.y
	};
	int indices = iOCT_rectangle2DIndices;

	GLuint newVAO;
	GLuint newVBO;
	GLuint newEBO;
	glGenVertexArrays(1, &newVAO);	// generate GL handles
	glGenBuffers(1, &newVBO);
	glGenBuffers(1, &newEBO);
	glBindVertexArray(newVAO);	// rest of the info binds 

	glBindBuffer(GL_ARRAY_BUFFER, newVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);		// start index, componentCount (2 = x, y), type, normalization, stride (# of bytes per component, 0 for tightly packed), offset from start
	glEnableVertexAttribArray(0);	// NOTE_SAME_INDEX_AS_ABOVE_;START

	glBindVertexArray(0); // unbind VAO first to keep VBO and EBO refs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	iOCT_glInfo info = { newVAO, newVBO, newEBO };
	return info;
}




