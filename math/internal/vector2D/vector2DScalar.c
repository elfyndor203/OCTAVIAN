#include "vector2D/vector2DScalar.h"
#include "standards/mathStandards_internal.h"
#include "definitions/operations_internal.h"

OCT_vector2D OCT_vec2_scal_add(OCT_vector2D vectorA, float scalar) {
	OCT_vector2D resultantVector = {
		.x = vectorA.x + scalar,
		.y = vectorA.y + scalar,
	};
	return resultantVector;
}

OCT_vector2D OCT_vec2_scal_sub(OCT_vector2D vectorA, float scalar) {
	OCT_vector2D resultantVector = {
		.x = vectorA.x - scalar,
		.y = vectorA.y - scalar,
	};
	return resultantVector;
}

OCT_vector2D OCT_vec2_scal_mult(OCT_vector2D vectorA, float scalar) {
	OCT_vector2D resultantVector = {
		.x = vectorA.x * scalar,
		.y = vectorA.y * scalar,
	};
	return resultantVector;
}

OCT_vector2D OCT_vec2_scal_div(OCT_vector2D vectorA, float scalar) {
	if (scalar == 0) {
		return vectorA;
	}
	OCT_vector2D resultantVector = {
		.x = vectorA.x / scalar,
		.y = vectorA.y / scalar,
	};
	return resultantVector;
}

OCT_vector2D OCT_vec2_rotate(OCT_vector2D vectorA, float radians) {
	OCT_vector2D resultantVector = OCT_origin2D;
	float cosTheta = cosf(radians);
	float sinTheta = sinf(radians);

	resultantVector.x = vectorA.x * cosTheta - vectorA.y * sinTheta;
	resultantVector.y = vectorA.x * sinTheta + vectorA.y * cosTheta;

	return resultantVector;
}