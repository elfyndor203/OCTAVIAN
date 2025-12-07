#include "vector2DVector2D_internal.h"

float OCT_vector2D_Dot(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	float dotProduct = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
	return dotProduct;
}

OCT_vector2D OCT_vector2D_vector2D(OCT_basicOperations operation, OCT_vector2D vectorA, OCT_vector2D vectorB) {
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

OCT_vector2D OCT_vector2D_Vector2DMulti(OCT_basicOperations operation, int vectorCount, OCT_vector2D* vectorArray) {
	OCT_vector2D resultantVector = vectorArray[0];
	// operates on the first vector using the rest
	for (int i = 1; i < vectorCount; i++) {
		resultantVector = OCT_vector2D_vector2D(operation, resultantVector, vectorArray[i]);
	}
	return resultantVector;
}

