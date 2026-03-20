#pragma once
#include "matrices/mat3.h"

OCT_mat3 OCT_mat3_identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};

OCT_mat3 OCT_mat3_mul(OCT_mat3 matA, OCT_mat3 matB) {
    OCT_mat3 result = {
        matA.c0r0 * matB.c0r0 + matA.c1r0 * matB.c0r1 + matA.c2r0 * matB.c0r2,  // c0r0
        matA.c0r1 * matB.c0r0 + matA.c1r1 * matB.c0r1 + matA.c2r1 * matB.c0r2,  // c0r1
        matA.c0r2 * matB.c0r0 + matA.c1r2 * matB.c0r1 + matA.c2r2 * matB.c0r2,  // c0r2
        matA.c0r0 * matB.c1r0 + matA.c1r0 * matB.c1r1 + matA.c2r0 * matB.c1r2,  // c1r0
        matA.c0r1 * matB.c1r0 + matA.c1r1 * matB.c1r1 + matA.c2r1 * matB.c1r2,  // c1r1
        matA.c0r2 * matB.c1r0 + matA.c1r2 * matB.c1r1 + matA.c2r2 * matB.c1r2,  // c1r2
        matA.c0r0 * matB.c2r0 + matA.c1r0 * matB.c2r1 + matA.c2r0 * matB.c2r2,  // c2r0
        matA.c0r1 * matB.c2r0 + matA.c1r1 * matB.c2r1 + matA.c2r1 * matB.c2r2,  // c2r1
        matA.c0r2 * matB.c2r0 + matA.c1r2 * matB.c2r1 + matA.c2r2 * matB.c2r2,  // c2r2
    };
    return result;
}
