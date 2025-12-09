#include "bufferGeneration_internal.h"
#include "_ECS_Output/_REN_include.h"

#include "OCT_Math.h"
#include "mesh/prototypes.h"
#include "shaders/shader/shader_internal.h"
#include "renderer/rendererObject/rendererObject_internal.h"
#include "renderer/layer/layer_internal.h"

const GLsizei defaultStride = 0;

iOCT_glInfo iOCT_generateBuffers(OCT_entityHandle entity, OCT_componentTypes componentType) {	// generates buffers for a new rendererObject
	GLuint vertexCount = 0;
	GLuint indexCount = 0;

	GLuint newVAO;																	// upload to GPU
	GLuint newVBO;
	GLuint newEBO;
	glGenVertexArrays(1, &newVAO);	// generate GL handles
	glGenBuffers(1, &newVBO);
	glGenBuffers(1, &newEBO);
	glBindVertexArray(newVAO);	// rest of the info binds 
	glBindBuffer(GL_ARRAY_BUFFER, newVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newEBO);

	switch (componentType) {
	case componentHitBox2D: {															// get vertex data
		printf("Requesting hitBox2D data from entity %zu\n", entity.entityID);
		OCT_rectangle2D hitBox = _REN_rectVertices_get(entity, componentType);
		float hitBoxVertices[OCT_RECTANGLE2D_VERTEXCOUNT * 2] = {
			hitBox.bottomLeft.x, hitBox.bottomLeft.y,
			hitBox.bottomRight.x, hitBox.bottomRight.y,
			hitBox.topRight.x, hitBox.topRight.y,
			hitBox.topLeft.x, hitBox.topLeft.y
		};
		vertexCount = 4;
		indexCount = 6;
		glBufferData(GL_ARRAY_BUFFER, sizeof(hitBoxVertices), hitBoxVertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iOCT_rectangle2DIndices), iOCT_rectangle2DIndices, GL_STATIC_DRAW);
		printf("Entity: %zu\nFirst Vertex:%f\n", entity.entityID, hitBoxVertices[0]);
		break;
	}
	}
	GLint size = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	printf("VBO size = %d (should match your vertices array size in bytes)\n", size);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);		// start index, componentCount (2 = x, y), type, normalization, stride (# of bytes per component, 0 for tightly packed), offset from start
	glEnableVertexAttribArray(0);	// NOTE_SAME_INDEX_AS_ABOVE_;START

	glBindVertexArray(0); // unbind VAO first to keep VBO and EBO refs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	iOCT_glInfo info = { newVAO, newVBO, newEBO, vertexCount, indexCount };
	return info;
}




