#pragma once
#include "vector2D.h"
#include "definitions/operations.h"

OCT_vector2D OCT_vector2D_scalar(OCT_basicOperations operation, OCT_vector2D vectorA, float scalar);

/// Radians
OCT_vector2D OCT_vector2D_rotate(OCT_vector2D vectorA, float angle);