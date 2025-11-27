#pragma once
#include "vectors/vector2DInfo.h"
#include "standards/mathStandards.h"

#include "vector2DVector2D_internal.h"

float vector2D_Magnitude(vector2D vectorA);
bool vector2D_isEqual(vector2D vectorA, vector2D vectorB, float threshold);
float vector2D_angle(vector2D vectorA, vector2D vectorB);