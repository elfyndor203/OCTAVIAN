#pragma once
#include "vectors/vector2DVector2D.h"
#include "standards/mathStandards.h"

#include <stdarg.h>
#include "definitions/operations_internal.h"

float vector2D_Dot(OCT_vector2D vectorA, OCT_vector2D vectorB);
OCT_vector2D vector2D_Vector2D(OCT_basicOperations operation, OCT_vector2D vectorA, OCT_vector2D vectorB);
OCT_vector2D vector2D_Vector2DMulti(OCT_basicOperations operation, int vectorCount, ...);

