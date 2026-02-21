#pragma once
#include <stdbool.h>
#include "definitions/operations.h"

typedef struct {
	float x;
	float y;
} OCT_vec2;

typedef OCT_vec2 OCT_vert2;
extern const OCT_vec2 OCT_vec2_zero;

float OCT_vec2_dot(OCT_vec2 vectorA, OCT_vec2 vectorB);
OCT_vec2 OCT_vec2_add(OCT_vec2 vectorA, OCT_vec2 vectorB);
OCT_vec2 OCT_vec2_sub(OCT_vec2 vectorA, OCT_vec2 vectorB);
OCT_vec2 OCT_vec2_mul_eleWise(OCT_vec2 vectorA, OCT_vec2 vectorB);
OCT_vec2 OCT_vec2_div_eleWise(OCT_vec2 vectorA, OCT_vec2 vectorB);
// OCT_vec2 OCT_vec2_multi(OCT_operations operation, int vectorCount, OCT_vec2* vectorArray);

OCT_vec2 OCT_vec2_mul(OCT_vec2 vectorA, float scalar);
OCT_vec2 OCT_vec2_div(OCT_vec2 vectorA, float scalar);
OCT_vec2 OCT_vec2_rotate(OCT_vec2 vectorA, float angle);

float OCT_vec2_mag(OCT_vec2 vectorA);
bool OCT_vec2_equal(OCT_vec2 vectorA, OCT_vec2 vectorB, float threshold);
float OCT_vec2_radians(OCT_vec2 vectorA, OCT_vec2 vectorB);
float OCT_vec2_degrees(OCT_vec2 vectorA, OCT_vec2 vectorB);


