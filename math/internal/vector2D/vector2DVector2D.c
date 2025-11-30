#include "vector2DVector2D_internal.h"

float vector2D_Dot(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	float dotProduct = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
	return dotProduct;
}

OCT_vector2D vector2D_Vector2D(OCT_basicOperations operation, OCT_vector2D vectorA, OCT_vector2D vectorB) {
	OCT_vector2D resultantVector;

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
			OCT_logError(ERR_DIVIDE_BY_ZERO);
			return vectorA;
		}
		resultantVector.x = vectorA.x / vectorB.x;
		resultantVector.y = vectorA.y / vectorB.y;
		break;

	default:
		OCT_logError(ERR_VECTOR_FAILED);
		return vectorA;
	}
	return resultantVector;
}

OCT_vector2D vector2D_Vector2DMulti(OCT_basicOperations operation, int vectorCount, ...) { // NOTE: IF UPDATED, MUST CHANGE API FUNCTION TOO
	va_list arguments;
	va_start(arguments, vectorCount);
	OCT_vector2D resultantVector = OCT_origin2D;

	for (int i = 0; i < vectorCount; i++) {
		OCT_vector2D vectorToAdd = va_arg(arguments, OCT_vector2D);

		resultantVector = vector2D_Vector2D(operation, resultantVector, vectorToAdd);
	}

	va_end(arguments);
	return resultantVector;
}

///API

float OCT_vector2D_Dot(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	return vector2D_Dot(vectorA, vectorB);
}

OCT_vector2D OCT_vector2D_Vector2D(OCT_basicOperations operation, OCT_vector2D vectorA, OCT_vector2D vectorB) {
	return vector2D_Vector2D(operation, vectorA, vectorB);
}

OCT_vector2D OCT_vector2D_Vector2DMulti(OCT_basicOperations operation, int vectorCount, ...) {	// NOTE: IF UPDATED, MUST CHANGE INTERNAL FUNCTION TOO
	va_list arguments;
	va_start(arguments, vectorCount);
	OCT_vector2D resultantVector = OCT_origin2D;

	for (int i = 0; i < vectorCount; i++) {
		OCT_vector2D vectorToAdd = va_arg(arguments, OCT_vector2D);

		resultantVector = vector2D_Vector2D(operation, resultantVector, vectorToAdd);
	}

	va_end(arguments);
	return resultantVector;
}

