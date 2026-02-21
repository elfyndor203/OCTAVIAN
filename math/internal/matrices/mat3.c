#pragma once
#include "matrices/mat3.h"

extern OCT_mat3 OCT_mat3x3_identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};

OCT_mat3 OCT_mat3_mul(OCT_mat3 matrixA, OCT_mat3 matrixB) {
    OCT_mat3 result = {
        matrixA.r0c0 * matrixB.r0c0 + matrixA.r0c1 * matrixB.r1c0 + matrixA.r0c2 * matrixB.r2c0,
        matrixA.r0c0 * matrixB.r0c1 + matrixA.r0c1 * matrixB.r1c1 + matrixA.r0c2 * matrixB.r2c1,
        matrixA.r0c0 * matrixB.r0c2 + matrixA.r0c1 * matrixB.r1c2 + matrixA.r0c2 * matrixB.r2c2,
        matrixA.r1c0 * matrixB.r0c0 + matrixA.r1c1 * matrixB.r1c0 + matrixA.r1c2 * matrixB.r2c0,
        matrixA.r1c0 * matrixB.r0c1 + matrixA.r1c1 * matrixB.r1c1 + matrixA.r1c2 * matrixB.r2c1,
        matrixA.r1c0 * matrixB.r0c2 + matrixA.r1c1 * matrixB.r1c2 + matrixA.r1c2 * matrixB.r2c2,
        matrixA.r2c0 * matrixB.r0c0 + matrixA.r2c1 * matrixB.r1c0 + matrixA.r2c2 * matrixB.r2c0,
        matrixA.r2c0 * matrixB.r0c1 + matrixA.r2c1 * matrixB.r1c1 + matrixA.r2c2 * matrixB.r2c1,
        matrixA.r2c0 * matrixB.r0c2 + matrixA.r2c1 * matrixB.r1c2 + matrixA.r2c2 * matrixB.r2c2,
    };
    return result;
}