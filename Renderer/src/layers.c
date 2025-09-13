#include "layers.h"

float firstVertices[] = {                    //actual points to be rendered
 0.0f,  0.75f, 0.0f,  // tip
 0.5f,  0.25f, 0.0f,  // tri base R
-0.5f,  0.25f, 0.0f,  // tri base L
 0.5f, -0.5f, 0.0f,  // bottom R
-0.5f, -0.5f, 0.0f,  // bottom L
-0.2f, 0.9f, 0.11f
};

unsigned int firstVerticesCount = 6;

void addToVertices(float amount) {
	for (int i = 0; i < sizeof(firstVertices) / sizeof(float); i++) {
		firstVertices[i] += amount;
	}
}