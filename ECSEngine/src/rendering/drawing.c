#include "drawing.h"
#include <stdlib.h>

layer* createNewLayer(bool visible) {
	layer* newLayer = malloc(sizeof(layer) + initialCapacity * sizeof(line*));
	if (!newLayer) {
		printf("Malloc for newLayer failed");
		return;
	}

	newLayer->visible = visible;
	newLayer->capacity = initialCapacity;
	newLayer->elementCount = 0;
}

void drawToLayer(line* line, layer* layer) {
	if (layer->elementCount == layer->capacity) {
		printf("capacity reached");
	}
	else {
		size_t newPosition = layer->elementCount;
		layer->elementCount += 1;
		layer->lines[newPosition] = line;
	}

	printf("%zu", layer->elementCount);
}