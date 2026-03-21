#pragma once
#include "vectors/vec2.h"

#define OCT_RECTANGLE2D_VERTEXCOUNT 4

/// Listed counterclockwise from the bottom left
typedef struct {
	OCT_vec2 origin;
	OCT_vec2 dimensions;
	float rotation;
} OCT_rect2;

OCT_rect2 OCT_rectangle2D_generate(OCT_vec2 center, OCT_vec2 dimensions, float rotation);