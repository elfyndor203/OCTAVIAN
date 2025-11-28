#pragma once
#include "vectors/vector2DVector2D.h"
#include "standards/mathStandards.h"

#include <stdarg.h>
#include "definitions/operations_internal.h"

float vector2D_Dot(vector2D vectorA, vector2D vectorB);
vector2D vector2D_Vector2D(OCT_basicOperations operation, vector2D vectorA, vector2D vectorB);
vector2D vector2D_Vector2DMulti(OCT_basicOperations operation, int vectorCount, ...);

