#include "vector2D.h"

#include <stdarg.h>

vector2D vector2D_addV(int vectorsCount, ...) {
	va_list(arguments);
	va_start(arguments, vectorsCount);
	vector2D resultantVector = originZeroZero;

	for (int i = 0; i < vectorsCount; i++) {
		vector2D vectorToAdd = va_arg(arguments, vector2D);

		resultantVector.x += (float)vectorToAdd.x;
		resultantVector.y += (float)vectorToAdd.y;
	}

	va_end(arguments);
	return resultantVector;
}

vector2D vector2D_addS(float scalar, vector2D vectorA) {
	vector2D resultantVector = originZeroZero;
	resultantVector.x += scalar;
	resultantVector.y += scalar;

	return resultantVector;
}


float vector2D_dot(vector2D vectorA, vector2D vectorB) {
	float dotProduct = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
	return dotProduct;
}

float vector2D_magnitude(vector2D vectorA) {
	double magnitude = (float)hypot(vectorA.x, vectorA.x);
	return magnitude;
}

float vector2D_angle(vector2D vectorA, vector2D vectorB) {
	float dotProduct = vector2D_dot(vectorA, vectorB);
	float magnitudeA = vector2D_magnitude(vectorA);
	float magnitudeB = vector2D_magnitude(vectorB);
	float angle = acos(dotProduct / (magnitudeA * magnitudeB));
	return angle;
}

bool vector2D_isEqual(vector2D vectorA, vector2D vectorB) {
	if (vectorA.x != vectorB.x) {
		return false;
	}
	if (vectorA.y != vectorB.y) {
		return false;
	}
	return true;
}

float floats_add(float floatOne, float floatTwo) {
	return floatOne + floatTwo;
}

float floats_subtract(float floatOne, float floatTwo) {
	return floatOne - floatTwo;
}

float floats_multiply(float floatOne, float floatTwo) {
	return floatOne * floatTwo;
}

float floats_divide(float floatOne, float floatTwo) {
	if (floatTwo == 0) {
		logError(ERR_DIVIDE_BY_ZERO);
		return floatOne;
	}
	return floatOne / floatTwo;
}

vector2D vector2D_elementWiseS(vector2D* vectorA, float scalar, genericFloatOperations operation) {
	vector2D resultantVector = { 0 };
	resultantVector.x = operation(vectorA->x, scalar);
	resultantVector.y = operation(vectorA->y, scalar);

	return resultantVector;
}
