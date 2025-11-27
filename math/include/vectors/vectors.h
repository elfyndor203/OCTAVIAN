#pragma once
typedef struct {
	float x;
	float y;
} vector2D;

typedef vector2D point2D;
static const point2D origin2D = { 0, 0 };

typedef struct {
	point2D localOrigin;
	point2D end;
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

