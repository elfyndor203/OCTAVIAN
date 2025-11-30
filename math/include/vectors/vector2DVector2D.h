#pragma once
#include "vectors.h"
#include "definitions/operations.h"

float OCT_vector2D_Dot(OCT_vector2D vectorA, OCT_vector2D vectorB);
OCT_vector2D OCT_vector2D_Vector2D(OCT_basicOperations operation, OCT_vector2D vectorA, OCT_vector2D vectorB);
OCT_vector2D OCT_vector2D_Vector2DMulti(OCT_basicOperations operation, int vectorCount, ...);
