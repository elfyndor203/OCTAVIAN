#pragma once
#include "vector2D/vector2D.h"

/// Listed counterclockwise from the bottom left
typedef struct {
	OCT_vertex2D origin;
	OCT_vector2D dimensions;
	float rotation;

	OCT_vertex2D bottomLeft;
	OCT_vertex2D bottomRight;
	OCT_vertex2D topRight;
	OCT_vertex2D topLeft;
} OCT_box2D;

OCT_box2D OCT_box2D_generate(OCT_vertex2D center, OCT_vector2D dimensions, float rotation);