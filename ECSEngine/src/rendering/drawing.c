 #include "drawing.h"
#include <stdlib.h>

layer* createNewLayer(bool visible) {
	layer* newLayer = mallocCheck((sizeof(layer) + initialCapacity * sizeof(line*)), "newLayer");

	newLayer->visible = visible;
	newLayer->capacity = initialCapacity;
	newLayer->elementCount = 0;

	return newLayer;
}

void drawLineToLayer(line* line, layer* layer) {
	if (layer->elementCount >= layer->capacity) {
		printf("capacity reached");
		// expandCapacity();
	}
	else {
		layer->elementCount += 1;

		size_t latestLine = layer->elementCount;
		layer->lines[latestLine] = line;
	}

	printf("%zu", layer->elementCount);
}
