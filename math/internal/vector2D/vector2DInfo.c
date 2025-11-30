#include "vector2DInfo_internal.h"

float vector2D_Magnitude(OCT_vector2D vectorA) {
	return hypotf(vectorA.x, vectorA.y);
}

bool vector2D_isEqual(OCT_vector2D vectorA, OCT_vector2D vectorB, float threshold) {
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

float vector2D_angle(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	float dotProduct = vector2D_Dot(vectorA, vectorB);
	float magnitudeA = vector2D_Magnitude(vectorA);
	float magnitudeB = vector2D_Magnitude(vectorB);
	float angle = acos(dotProduct / (magnitudeA * magnitudeB));
	return angle;
}

/// API

float OCT_vector2D_Magnitude(OCT_vector2D vectorA) {
	return vector2D_Magnitude(vectorA);
}
bool OCT_vector2D_isEqual(OCT_vector2D vectorA, OCT_vector2D vectorB, float threshold) {
	return vector2D_isEqual(vectorA, vectorB, threshold);
}
float OCT_vector2D_angle(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	return vector2D_angle(vectorA, vectorB);
}
