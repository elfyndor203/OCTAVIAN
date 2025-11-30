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

typedef struct {
	float x;
	float y;
	float z;
} OCT_vector3D;

typedef OCT_vector3D OCT_vertex3D;
static const OCT_vertex3D OCT_origin3D = { 0, 0 };

typedef struct {
	OCT_vertex3D localOrigin;
	OCT_vertex3D end;
} OCT_line3D;


