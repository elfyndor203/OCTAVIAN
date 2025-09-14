#pragma once
#include "math/vectors.h"

typedef struct gameObject gameObject;

typedef struct {
	size_t poolIndex;
	size_t parentIndex;
	float rotation2D;
	vector2D scale2D;
} transform2D;