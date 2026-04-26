#pragma once
#include "matrices/mat3.h"

#include <math.h>
#include <assert.h>
#include <stdio.h>

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

OCT_vec3 OCT_mat3_mulVec3(OCT_mat3 mat, OCT_vec3 vec) {
    OCT_vec3 result = {
        mat.c0r0 * vec.x + mat.c1r0 * vec.y + mat.c2r0 * vec.z,
        mat.c0r1 * vec.x + mat.c1r1 * vec.y + mat.c2r1 * vec.z,
        mat.c0r2 * vec.x + mat.c1r2 * vec.y + mat.c2r2 * vec.z
    };

    return result;
}

OCT_mat3 OCT_mat3_generate(OCT_vec2 translation, OCT_vec2 scale, float rotation) {
    float cosRot = cosf(rotation);
    float sinRot = sinf(rotation);
    OCT_mat3 result = {
        scale.x * cosRot, scale.x * sinRot, 0,
        -scale.y * sinRot, scale.y * cosRot, 0,
        translation.x, translation.y, 1
    };
    return result;
}

OCT_mat3 OCT_mat3_inverse(OCT_mat3 m) {
    float det = m.c0r0 * (m.c1r1 * m.c2r2 - m.c2r1 * m.c1r2)
        - m.c1r0 * (m.c0r1 * m.c2r2 - m.c2r1 * m.c0r2)
        + m.c2r0 * (m.c0r1 * m.c1r2 - m.c1r1 * m.c0r2);

    assert(det != 0);
    float invDet = 1.0f / det;

    OCT_mat3 result;
    result.c0r0 = (m.c1r1 * m.c2r2 - m.c1r2 * m.c2r1) * invDet;
    result.c0r1 = -(m.c0r1 * m.c2r2 - m.c0r2 * m.c2r1) * invDet;
    result.c0r2 = (m.c0r1 * m.c1r2 - m.c0r2 * m.c1r1) * invDet;
    result.c1r0 = -(m.c1r0 * m.c2r2 - m.c1r2 * m.c2r0) * invDet;
    result.c1r1 = (m.c0r0 * m.c2r2 - m.c0r2 * m.c2r0) * invDet;
    result.c1r2 = -(m.c0r0 * m.c1r2 - m.c0r2 * m.c1r0) * invDet;
    result.c2r0 = (m.c1r0 * m.c2r1 - m.c1r1 * m.c2r0) * invDet;
    result.c2r1 = -(m.c0r0 * m.c2r1 - m.c0r1 * m.c2r0) * invDet;
    result.c2r2 = (m.c0r0 * m.c1r1 - m.c0r1 * m.c1r0) * invDet;
    return result;
}

void OCT_mat3_print(OCT_mat3 m) {
    printf("[%.2f, %.2f, %.2f]\n", m.c0r0, m.c1r0, m.c2r0);
    printf("[%.2f, %.2f, %.2f]\n", m.c0r1, m.c1r1, m.c2r1);
    printf("[%.2f, %.2f, %.2f]\n", m.c0r2, m.c1r2, m.c2r2);
}