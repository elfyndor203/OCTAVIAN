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

vector2D addVectors2D(int vectorsCount, ...);
vector2D addScalarToVector2D(float scalar, vector2D vectorA);

float dotProductVectors2D(vector2D vectorA, vector2D vectorB);
float angleBetweenVectors2D(vector2D vectorA, vector2D vectorB);
bool isEqual(vector2D vectorA, vector2D vectorB);

float magnitudeVector2D(vector2D vectorA);

float addFloats(float floatOne, float floatTwo);
float subtractFloats(float floatOne, float floatTwo);
float multiplyFloats(float floatOne, float floatTwo);
float divideFloats(float floatOne, float floatTwo);

vector2D vector2DScalarElementWise(vector2D* vectorA, float scalar, genericFloatOperations operation);
