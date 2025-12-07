#include "vector2DInfo_internal.h"

float OCT_vector2D_Magnitude(OCT_vector2D vectorA) {
	return hypotf(vectorA.x, vectorA.y);
}

bool OCT_vector2D_isEqual(OCT_vector2D vectorA, OCT_vector2D vectorB, float threshold) {
	if (threshold <= 0.0f) {
		threshold = DEFAULT_EQUAL_THRESHOLD;
	}

	if (fabsf(vectorB.x - vectorA.x) < threshold && fabsf(vectorB.y - vectorA.y) < threshold) {
		return true;
	}
	else {
		return false;
	}
}

float OCT_vector2D_angle(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	float dotProduct = OCT_vector2D_Dot(vectorA, vectorB);
	float magnitudeA = OCT_vector2D_Magnitude(vectorA);
	float magnitudeB = OCT_vector2D_Magnitude(vectorB);
	float angle = acos(dotProduct / (magnitudeA * magnitudeB));
	return angle;
}
