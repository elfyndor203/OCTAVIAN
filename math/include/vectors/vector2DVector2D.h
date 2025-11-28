#pragma once
#include "vectors.h"
#include "definitions/operations.h"

float OCT_vector2D_Dot(vector2D vectorA, vector2D vectorB);
vector2D OCT_vector2D_Vector2D(OCT_basicOperations operation, vector2D vectorA, vector2D vectorB);
vector2D OCT_vector2D_Vector2DMulti(OCT_basicOperations operation, int vectorCount, ...);
