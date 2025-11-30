#pragma once
typedef struct {
	float x;
	float y;
} vector2D;

typedef vector2D vertex2D;
static const vertex2D origin2D = { 0, 0 };

typedef struct {
	vertex2D localOrigin;
	vertex2D end;
} line2D;

typedef struct {
	float x;
	float y;
	float z;
} vector3D;

typedef vector3D point3D;
static const point3D origin3D = { 0, 0 };

typedef struct {
	point3D localOrigin;
	point3D end;
} line3D;

