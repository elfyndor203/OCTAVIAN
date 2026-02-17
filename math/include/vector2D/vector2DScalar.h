#pragma once
#include "vector2D.h"
#include "definitions/operations.h"

OCT_vector2D OCT_vec2_scal(OCT_basicOperations operation, OCT_vector2D vectorA, float scalar);
OCT_vector2D OCT_vec2_scal_add(OCT_vector2D vectorA, float scalar);
OCT_vector2D OCT_vec2_scal_sub(OCT_vector2D vectorA, float scalar);
OCT_vector2D OCT_vec2_scal_mult(OCT_vector2D vectorA, float scalar);
OCT_vector2D OCT_vec2_scal_div(OCT_vector2D vectorA, float scalar);

/// Radians
OCT_vector2D OCT_vec2_rotate(OCT_vector2D vectorA, float angle);