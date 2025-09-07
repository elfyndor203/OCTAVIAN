#pragma once
#include "myStandards.h"
#include "vectors.h"
#include "colors.h"

#define initialCapacity 10

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
	line* lines[initialCapacity];
	size_t sprites[initialCapacity];
} layer;

layer* createNewLayer(bool visible);

// 



void drawLineToLayer(line* line, layer* layer);