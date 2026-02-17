#include "vector2D/vector2DVector2D.h"
#include "standards/mathStandards_internal.h"
#include "definitions/operations_internal.h"
#include <stdarg.h>

typedef OCT_vector2D(*OCT_vector2D_vector2D_Fx)(OCT_vector2D, OCT_vector2D); // Vector2D operation function pointer

static OCT_vector2D_vector2D_Fx iOCT_vec2_vec2_Fx[4] = {
	OCT_vec2_vec2_add,
	OCT_vec2_vec2_sub,
	OCT_vec2_vec2_mult,
	OCT_vec2_vec2_div
};	// NOTE: must match basicOperations enum in math

/// <summary>
/// Performs element-wise addition on the two vectors and returns the value of the result
/// </summary>
/// <param name="vectorA"></param>
/// <param name="vectorB"></param>
/// <returns></returns>
OCT_vector2D OCT_vec2_vec2_add(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	OCT_vector2D resultantVector = {
		.x = vectorA.x + vectorB.x,
		.y = vectorA.y + vectorB.y,
	};
	return resultantVector;
}

/// <summary>
/// Performs element-wise subtraction on the two vectors and returns the value of the result
/// </summary>
/// <param name="vectorA"></param>
/// <param name="vectorB"></param>
/// <returns></returns>
OCT_vector2D OCT_vec2_vec2_sub(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	OCT_vector2D resultantVector = {
		.x = vectorA.x - vectorB.x,
		.y = vectorA.y - vectorB.y,
	};
	return resultantVector;
}

/// <summary>
/// Performs element-wise multiplication on the two vectors and returns the value of the result
/// </summary>
/// <param name="vectorA"></param>
/// <param name="vectorB"></param>
/// <returns></returns>
OCT_vector2D OCT_vec2_vec2_mult(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	OCT_vector2D resultantVector = {
		.x = vectorA.x * vectorB.x,
		.y = vectorA.y * vectorB.y,
	};
	return resultantVector;
}

/// <summary>
/// Performs element-wise division on the two vectors and returns the value of the result
/// </summary>
/// <param name="vectorA"></param>
/// <param name="vectorB"></param>
/// <returns></returns>
OCT_vector2D OCT_vec2_vec2_div(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	if (vectorB.x == 0 || vectorB.y == 0) {
		return vectorA;
	}
	OCT_vector2D resultantVector = {
		.x = vectorA.x / vectorB.x,
		.y = vectorA.y / vectorB.y,
	};
	return resultantVector;
}

float OCT_vec2_dot(OCT_vector2D vectorA, OCT_vector2D vectorB) {
	float dotProduct = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
	return dotProduct;
}

OCT_vector2D OCT_vec2_vec2_multi(OCT_basicOperations operation, int vectorCount, OCT_vector2D* vectorArray) {
	OCT_vector2D resultantVector = vectorArray[0];
	// operates on the first vector using the rest
	for (int i = 1; i < vectorCount; i++) {
		resultantVector = iOCT_vec2_vec2_Fx[operation](resultantVector, vectorArray[i]);
	}
	return resultantVector;
}

