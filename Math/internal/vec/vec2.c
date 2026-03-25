#include "vectors/vec2.h"
#include "units/conversions.h"
#include "definitions/defaultValues_internal.h"
#include <math.h>

const OCT_vec2 OCT_vec2_zero = { 0, 0 };
typedef OCT_vec2(*OCT_vector2D_vector2D_Fx)(OCT_vec2, OCT_vec2); // Vector2D operation function pointer

static OCT_vector2D_vector2D_Fx iOCT_vec2_Fx[4] = {
	OCT_vec2_add,
	OCT_vec2_sub,
	OCT_vec2_mul_eleWise,
	OCT_vec2_div_eleWise
};	// NOTE: must match basicOperations enum in math

/// <summary>
/// Performs element-wise addition on the two vectors and returns the value of the result
/// </summary>
/// <param name="vectorA"></param>
/// <param name="vectorB"></param>
/// <returns></returns>
OCT_vec2 OCT_vec2_add(OCT_vec2 vectorA, OCT_vec2 vectorB) {
	OCT_vec2 resultantVector = {
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
OCT_vec2 OCT_vec2_sub(OCT_vec2 vectorA, OCT_vec2 vectorB) {
	OCT_vec2 resultantVector = {
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
OCT_vec2 OCT_vec2_mul_eleWise(OCT_vec2 vectorA, OCT_vec2 vectorB) {
	OCT_vec2 resultantVector = {
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
OCT_vec2 OCT_vec2_div_eleWise(OCT_vec2 vectorA, OCT_vec2 vectorB) {
	if (vectorB.x == 0 || vectorB.y == 0) {
		return vectorA;
	}
	OCT_vec2 resultantVector = {
		.x = vectorA.x / vectorB.x,
		.y = vectorA.y / vectorB.y,
	};
	return resultantVector;
}
float OCT_vec2_dot(OCT_vec2 vectorA, OCT_vec2 vectorB) {
	float dotProduct = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
	return dotProduct;
}
OCT_vec2 OCT_vec2_multi(OCT_operations operation, int vectorCount, OCT_vec2* vectorArray) {
	OCT_vec2 resultantVector = vectorArray[0];
	// operates on the first vector using the rest
	for (int i = 1; i < vectorCount; i++) {
		resultantVector = iOCT_vec2_Fx[operation](resultantVector, vectorArray[i]);
	}
	return resultantVector;
}

// SCALAR
OCT_vec2 OCT_vec2_mul(OCT_vec2 vectorA, float scalar) {
	OCT_vec2 resultantVector = {
		.x = vectorA.x * scalar,
		.y = vectorA.y * scalar,
	};
	return resultantVector;
}
OCT_vec2 OCT_vec2_div(OCT_vec2 vectorA, float scalar) {
	if (scalar == 0) {
		return vectorA;
	}
	OCT_vec2 resultantVector = {
		.x = vectorA.x / scalar,
		.y = vectorA.y / scalar,
	};
	return resultantVector;
}
OCT_vec2 OCT_vec2_rotate(OCT_vec2 vectorA, float radians) {
	OCT_vec2 resultantVector = OCT_vec2_zero;
	float cosTheta = cosf(radians);
	float sinTheta = sinf(radians);

	resultantVector.x = vectorA.x * cosTheta - vectorA.y * sinTheta;
	resultantVector.y = vectorA.x * sinTheta + vectorA.y * cosTheta;

	return resultantVector;
}

// INFO
float OCT_vec2_mag(OCT_vec2 vectorA) {
	return hypotf(vectorA.x, vectorA.y);
}
bool OCT_vec2_equal(OCT_vec2 vectorA, OCT_vec2 vectorB, float threshold) {
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
float OCT_vec2_radians(OCT_vec2 vectorA, OCT_vec2 vectorB) {
	float dotProduct = OCT_vec2_dot(vectorA, vectorB);
	float magnitudeA = OCT_vec2_mag(vectorA);
	float magnitudeB = OCT_vec2_mag(vectorB);
	float angle = acosf(dotProduct / (magnitudeA * magnitudeB));
	return angle;
}
float OCT_vec2_degrees(OCT_vec2 vectorA, OCT_vec2 vectorB) {
	return OCT_rad2deg(OCT_vec2_radians(vectorA, vectorB));
}