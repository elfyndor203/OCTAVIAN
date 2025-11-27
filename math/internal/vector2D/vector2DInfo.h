#pragma once
#include "vectors/vector2DInfo.h"
#include "standards/mathStandards.h"

float vector2D_Magnitude(vector2D vectorA) {
	return hypotf(vectorA.x, vectorA.y);
}

int vector2D_isEqual(vector2D vectorA, vector2D vectorB) {
	if (vectorA.x = vectorB.x && vectorA.y == vectorB.y) {
		return 1;
	}
	else if (vector2D_Magnitude(vectorA) == vector2D_Magnitude(vectorB)) {
		return -1;
	}
	else {
		return 0;
	}
}