#pragma once
#include "vectors/vec2.h"

#define OCT_RECTANGLE2D_VERTEXCOUNT 4

/// Listed counterclockwise from the bottom left
typedef struct {
	OCT_vert2 origin;
	OCT_vec2 dimensions;
	float rotation;

	OCT_vert2 bottomLeft;
	OCT_vert2 bottomRight;
	OCT_vert2 topRight;
	OCT_vert2 topLeft;
} OCT_rectangle2D;

OCT_rectangle2D OCT_rectangle2D_generate(OCT_vert2 center, OCT_vec2 dimensions, float rotation);