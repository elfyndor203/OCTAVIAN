#include "vector2DScalar_internal.h"

OCT_vector2D vector2D_Scalar(OCT_basicOperations operation, OCT_vector2D vectorA, float scalar) {
	OCT_vector2D resultantVector = OCT_origin2D;

	switch(operation) {
		case OCT_OP_ADD:
			resultantVector.x = vectorA.x + scalar;
			resultantVector.y = vectorA.y + scalar;
			break;
		case OCT_OP_SUBTRACT:
			resultantVector.x = vectorA.x - scalar;
			resultantVector.y = vectorA.y - scalar;
			break;
		case OCT_OP_MULTIPLY:
			resultantVector.x = vectorA.x * scalar;
			resultantVector.y = vectorA.y * scalar;
			break;
		case OCT_OP_DIVIDE:
			if (scalar == 0) {
				OCT_logError(ERR_DIVIDE_BY_ZERO);
				return vectorA;
			}	
			resultantVector.x = vectorA.x / scalar;
			resultantVector.y = vectorA.y / scalar;
			break;
		default:
			OCT_logError(ERR_VECTOR_FAILED);
			return vectorA;
	}

	return resultantVector;
}

/// API

OCT_vector2D OCT_vector2D_Scalar(OCT_basicOperations operation, OCT_vector2D vectorA, float scalar) {
	return vector2D_Scalar(operation, vectorA, scalar);
}