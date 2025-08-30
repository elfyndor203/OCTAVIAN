#pragma once
#include "vectors.h"

typedef struct gameObject gameObject;

typedef struct {
	gameObject* parent;
	vector2D globalPosition2D;
	vector2D localPosition2D;
} position2D;

position2D* createDefaultPosition2D(gameObject* parent);
