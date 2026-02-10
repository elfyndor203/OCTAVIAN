#pragma once
typedef struct {
	float x;
	float y;
} OCT_vector2D;

typedef OCT_vector2D OCT_vertex2D;
static const OCT_vertex2D OCT_origin2D = { 0, 0 };

typedef struct {
	OCT_vertex2D localOrigin;
	OCT_vertex2D end;
} OCT_line2D;


