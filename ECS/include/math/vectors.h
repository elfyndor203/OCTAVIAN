#pragma once
#include "myStandards.h"

typedef struct {
	float x;
	float y;
} vector2D;

typedef struct {
	vector2D origin;
	vector2D end;
} line2D;

static const vector2D originZeroZero = { 0, 0 };

vector2D addVectors2D(int vectorsCount, ...);
vector2D addScalarToVector2D(float scalar, vector2D vectorA);

float dotProductVectors2D(vector2D vectorA, vector2D vectorB);
float angleBetweenVectors2D(vector2D vectorA, vector2D vectorB);
bool isEqual(vector2D vectorA, vector2D vectorB);

float magnitudeVector2D(vector2D vectorA);

