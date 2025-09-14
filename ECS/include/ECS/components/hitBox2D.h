#pragma once
#include "math/vectors.h"

#define defaultHitBoxSize 1.0f

typedef struct gameObject gameObject;

typedef struct {
	size_t poolIndex;
	size_t parentIndex;
	vector2D origin; // bottom right corner
	float width;
	float height;

	vector2D center;
	vector2D bottom;
	vector2D right;
	vector2D top;
	vector2D left;
} hitBox2D;

hitBox2D* createDefaultHitBox2D(gameObject* parent);

void initializeHitBox2DVectors(hitBox2D* hitBox2DToSet);