#pragma once

#include "vectors/vec2.h"
#include "vectors/vec3.h"

/// <summary>
/// Row-major 3x3 matrix
/// </summary>
typedef struct OCT_mat3 {
	float c0r0;
	float c0r1;
	float c0r2;

	float c1r0;
	float c1r1;
	float c1r2;

	float c2r0;
	float c2r1;
	float c2r2;
} OCT_mat3;

extern OCT_mat3 OCT_mat3_identity;

OCT_mat3 OCT_mat3_mul(OCT_mat3 matrixA, OCT_mat3 matrixB);
OCT_vec3 OCT_mat3_mulVec(OCT_mat3 matrix, OCT_vec3 vector);
