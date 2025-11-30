#pragma once
#include "vectors/vector2DInfo.h"
#include "standards/mathStandards.h"

#include "vector2DVector2D_internal.h"

float vector2D_Magnitude(OCT_vector2D vectorA);
bool vector2D_isEqual(OCT_vector2D vectorA, OCT_vector2D vectorB, float threshold);
float vector2D_angle(OCT_vector2D vectorA, OCT_vector2D vectorB);