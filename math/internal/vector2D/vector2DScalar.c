#include "vector2DScalar_internal.h"

vector2D vector2D_Scalar(vector2D vectorA, float scalar, int operation) {
	vector2D newVector = origin2D;

	switch(operation) {
		case OP_ADD:
			newVector.x = vectorA.x + scalar;
			newVector.y = vectorA.y + scalar;
		case OP_SUBTRACT:
			newVector.x = vectorA.x - scalar;
			newVector.y = vectorA.y - scalar;
		case OP_MULTIPLY:
			newVector.x = vectorA.x * scalar;
			newVector.y = vectorA.y * scalar;
		case OP_DIVIDE:
			if (scalar == 0) {
				logError(ERR_DIVIDE_BY_ZERO);
				return vectorA;
			}	
			newVector.x = vectorA.x - scalar;
			newVector.y = vectorA.y - scalar;
	}
}

