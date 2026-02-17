#pragma once

/// <summary>
/// Row-major 3x3 matrix
/// </summary>
typedef struct OCT_matrix3x3 {
	float matrix[3][3];
} OCT_matrix3x3;

extern OCT_matrix3x3 OCT_mat3x3_identity;

OCT_matrix3x3 OCT_mat3x3_mult(OCT_matrix3x3 matrixA, OCT_matrix3x3 matrixB);