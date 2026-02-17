#pragma once
#include "vector2D.h"
#include "definitions/operations.h"

float OCT_vec2_dot(OCT_vector2D vectorA, OCT_vector2D vectorB);
OCT_vector2D OCT_vec2_vec2_add(OCT_vector2D vectorA, OCT_vector2D vectorB);
OCT_vector2D OCT_vec2_vec2_sub(OCT_vector2D vectorA, OCT_vector2D vectorB);
OCT_vector2D OCT_vec2_vec2_mult(OCT_vector2D vectorA, OCT_vector2D vectorB);
OCT_vector2D OCT_vec2_vec2_div(OCT_vector2D vectorA, OCT_vector2D vectorB);

OCT_vector2D OCT_vec2_vec2_multi(OCT_basicOperations operation, int vectorCount, OCT_vector2D* vectorArray);