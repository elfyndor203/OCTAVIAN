#include "vector2DVector2D_internal.h"

float vector2D_Dot(vector2D vectorA, vector2D vectorB) {
	float dotProduct = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
	return dotProduct;
}

vector2D vector2D_Vector2D(OCT_basicOperations operation, vector2D vectorA, vector2D vectorB) {
	vector2D resultantVector;

	switch (operation) {
	case OCT_OP_ADD:
		resultantVector.x = vectorA.x + vectorB.x;
		resultantVector.y = vectorA.y + vectorB.y;
		break;
	case OCT_OP_SUBTRACT:
		resultantVector.x = vectorA.x - vectorB.x;
		resultantVector.y = vectorA.y - vectorB.y;
		break;
	case OCT_OP_MULTIPLY:
		resultantVector.x = vectorA.x * vectorB.x;
		resultantVector.y = vectorA.y * vectorB.y;
		break;
	case OCT_OP_DIVIDE:
		if (vectorB.x == 0 || vectorB.y == 0) {
			logError(ERR_DIVIDE_BY_ZERO);
			return vectorA;
		}
		resultantVector.x = vectorA.x / vectorB.x;
		resultantVector.y = vectorA.y / vectorB.y;
		break;

	default:
		logError(ERR_VECTOR_FAILED);
		return vectorA;
	}
	return resultantVector;
}

vector2D vector2D_Vector2DMulti(int vectorCount, OCT_basicOperations operation, ...) { // NOTE: IF UPDATED, MUST CHANGE API FUNCTION TOO
	va_list arguments;
	va_start(arguments, vectorCount);
	vector2D resultantVector = origin2D;

	for (int i = 0; i < vectorCount; i++) {
		vector2D vectorToAdd = va_arg(arguments, vector2D);

		resultantVector = vector2D_Vector2D(operation, resultantVector, vectorToAdd);
	}

	va_end(arguments);
	return resultantVector;
}

///API

float OCT_vector2D_Dot(vector2D vectorA, vector2D vectorB) {
	return vector2D_Dot(vectorA, vectorB);
}

vector2D OCT_vector2D_Vector2D(OCT_basicOperations operation, vector2D vectorA, vector2D vectorB) {
	return vector2D_Vector2D(operation, vectorA, vectorB);
}

vector2D OCT_vector2D_Vector2DMulti(int vectorCount, OCT_basicOperations operation, ...) {	// NOTE: IF UPDATED, MUST CHANGE INTERNAL FUNCTION TOO
	va_list arguments;
	va_start(arguments, vectorCount);
	vector2D resultantVector = origin2D;

	for (int i = 0; i < vectorCount; i++) {
		vector2D vectorToAdd = va_arg(arguments, vector2D);

		resultantVector = vector2D_Vector2D(operation, resultantVector, vectorToAdd);
	}

	va_end(arguments);
	return resultantVector;
}

