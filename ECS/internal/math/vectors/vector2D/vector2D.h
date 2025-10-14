#pragma once
#include "standards/myStandards.h"

typedef struct {
	float x;
	float y;
} vector2D;

typedef vector2D point2D;

typedef struct {
	point2D localOrigin;
	point2D end;
} line2D;

typedef float (*genericFloatOperations)(float, float);

static const point2D originZeroZero = { 0, 0 };

vector2D vector2D_addV(int vectorsCount, ...);
vector2D vector2D_addS(float scalar, vector2D vectorA);

float vector2D_dot(vector2D vectorA, vector2D vectorB);
float vector2D_angle(vector2D vectorA, vector2D vectorB);
bool vector2D_isEqual(vector2D vectorA, vector2D vectorB);

float vector2D_magnitude(vector2D vectorA);

float floats_add(float floatOne, float floatTwo);
float floats_subtract(float floatOne, float floatTwo);
float floats_multiply(float floatOne, float floatTwo);
float floats_divide(float floatOne, float floatTwo);

vector2D vector2D_elementWiseS(vector2D* vectorA, float scalar, genericFloatOperations operation);
