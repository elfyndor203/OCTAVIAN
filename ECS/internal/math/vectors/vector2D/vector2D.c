#include <stdarg.h>
#include "standards/myStandards.h"

#include "vector2D.h"

vector2D addVectors2D(int vectorsCount, ...) {
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

vector2D addScalarToVector2D(float scalar, vector2D vectorA) {
	vector2D resultantVector = originZeroZero;
	resultantVector.x += scalar;
	resultantVector.y += scalar;

	return resultantVector;
}


float dotProductVectors2D(vector2D vectorA, vector2D vectorB) {
	float dotProduct = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
	return dotProduct;
}

float magnitudeVector2D(vector2D vectorA) {
	double magnitude = (float)hypot(vectorA.x, vectorA.x);
	return magnitude;
}

float angleBetweenVectors2D(vector2D vectorA, vector2D vectorB) {
	float dotProduct = dotProductVectors2D(vectorA, vectorB);
	float magnitudeA = magnitudeVector2D(vectorA);
	float magnitudeB = magnitudeVector2D(vectorB);
	float angle = acos(dotProduct / (magnitudeA * magnitudeB));
	return angle;
}

bool isEqual(vector2D vectorA, vector2D vectorB) {
	if (vectorA.x != vectorB.x) {
		return false;
	}
	if (vectorA.y != vectorB.y) {
		return false;
	}
	return true;
}

float addFloats(float floatOne, float floatTwo) {
	return floatOne + floatTwo;
}

float subtractFloats(float floatOne, float floatTwo) {
	return floatOne - floatTwo;
}

float multiplyFloats(float floatOne, float floatTwo) {
	return floatOne * floatTwo;
}

float divideFloats(float floatOne, float floatTwo) {
	if (floatTwo == 0) {
		logError(ERR_DIVIDE_BY_ZERO);
		return floatOne;
	}
	return floatOne / floatTwo;
}

vector2D vector2DScalarElementWise(vector2D* vectorA, float scalar, genericFloatOperations operation) {
	vector2D resultantVector = { 0 };
	resultantVector.x = operation(vectorA->x, scalar);
	resultantVector.y = operation(vectorA->y, scalar);

	return resultantVector;
}
