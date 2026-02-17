#pragma once
#include "matrix2D/matrix2D.h"

extern OCT_matrix3x3 OCT_mat3x3_identity = { {{1,0,0},{0,1,0},{0,0,1}} };

OCT_matrix3x3 OCT_mat3x3_mult(OCT_matrix3x3 matrixA, OCT_matrix3x3 matrixB) {
    OCT_matrix3x3 result;

    result.matrix[0][0] = matrixA.matrix[0][0] * matrixB.matrix[0][0] + matrixA.matrix[0][1] * matrixB.matrix[1][0] + matrixA.matrix[0][2] * matrixB.matrix[2][0];
    result.matrix[0][1] = matrixA.matrix[0][0] * matrixB.matrix[0][1] + matrixA.matrix[0][1] * matrixB.matrix[1][1] + matrixA.matrix[0][2] * matrixB.matrix[2][1];
    result.matrix[0][2] = matrixA.matrix[0][0] * matrixB.matrix[0][2] + matrixA.matrix[0][1] * matrixB.matrix[1][2] + matrixA.matrix[0][2] * matrixB.matrix[2][2];
    result.matrix[1][0] = matrixA.matrix[1][0] * matrixB.matrix[0][0] + matrixA.matrix[1][1] * matrixB.matrix[1][0] + matrixA.matrix[1][2] * matrixB.matrix[2][0];
    result.matrix[1][1] = matrixA.matrix[1][0] * matrixB.matrix[0][1] + matrixA.matrix[1][1] * matrixB.matrix[1][1] + matrixA.matrix[1][2] * matrixB.matrix[2][1];
    result.matrix[1][2] = matrixA.matrix[1][0] * matrixB.matrix[0][2] + matrixA.matrix[1][1] * matrixB.matrix[1][2] + matrixA.matrix[1][2] * matrixB.matrix[2][2];
    result.matrix[2][0] = matrixA.matrix[2][0] * matrixB.matrix[0][0] + matrixA.matrix[2][1] * matrixB.matrix[1][0] + matrixA.matrix[2][2] * matrixB.matrix[2][0];
    result.matrix[2][1] = matrixA.matrix[2][0] * matrixB.matrix[0][1] + matrixA.matrix[2][1] * matrixB.matrix[1][1] + matrixA.matrix[2][2] * matrixB.matrix[2][1];
    result.matrix[2][2] = matrixA.matrix[2][0] * matrixB.matrix[0][2] + matrixA.matrix[2][1] * matrixB.matrix[1][2] + matrixA.matrix[2][2] * matrixB.matrix[2][2];

    return result;
}