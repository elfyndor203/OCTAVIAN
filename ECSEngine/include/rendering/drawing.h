#pragma once
#include "myStandards.h"
#include "vectors.h"
#include "colors.h"

#define initialCapacity 4

typedef struct {
	vector2D origin;
	vector2D vector;
	size_t width;
	myRGB color;
} line;

typedef struct {
	bool visible;
	size_t capacity;
	size_t elementCount;
	line* lines[];
} layer;

layer* createNewLayer(bool visible);
void drawToLayer(line* line, layer* layer);