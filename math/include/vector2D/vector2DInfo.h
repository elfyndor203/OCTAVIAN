#pragma once
#include "vector2D.h"

float OCT_vector2D_Magnitude(OCT_vector2D vectorA);
bool OCT_vector2D_isEqual(OCT_vector2D vectorA, OCT_vector2D vectorB, float threshold);
float OCT_vector2D_angle(OCT_vector2D vectorA, OCT_vector2D vectorB);