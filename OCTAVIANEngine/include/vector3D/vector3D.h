#pragma once
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