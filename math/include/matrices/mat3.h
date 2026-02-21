#pragma once

/// <summary>
/// Row-major 3x3 matrix
/// </summary>
typedef struct OCT_mat3 {
	float r0c0;
	float r0c1;
	float r0c2;
	float r1c0;
	float r1c1;
	float r1c2;
	float r2c0;
	float r2c1;
	float r2c2;

} OCT_mat3;

extern OCT_mat3 OCT_mat3x3_identity;

OCT_mat3 OCT_mat3_mul(OCT_mat3 matrixA, OCT_mat3 matrixB);