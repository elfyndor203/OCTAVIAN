#pragma once
#include "math/vectors.h"

typedef struct gameObject gameObject;

typedef struct {
	gameObject* parent;
	float rotation2D;
	vector2D scale2D;
} transform2D;