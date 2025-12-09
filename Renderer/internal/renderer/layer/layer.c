#include "layer_internal.h"

#include <stdlib.h>

iOCT_layer* iOCT_layerPool[iOCT_LAYER_MAX]; /// pointers
OCT_counter iOCT_layerCounter = 0;

iOCT_rendererObjectHandle iOCT_rendererObjectMap[64][1024][componentsTotal]; //NOTE_URGENT_HARDCODED

iOCT_layer* iOCT_layer_get(iOCT_layerID layerID) {
	if (layerID > iOCT_LAYER_MAX || iOCT_layerPool[layerID] == 0) {
		OCT_logError(ERR_ENTITYSET_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	//printf("Got layer #%zu\n", layerID);
	return iOCT_layerPool[layerID];
}

// mirrors entitySet, but has no need for a root object
iOCT_layerID iOCT_layer_new() {
	iOCT_layer* newLayer = calloc(1, sizeof(iOCT_layer));

	if (!newLayer) {
		OCT_logError(EXIT_LAYER_FAILED);				//NOTE: 2 EXITS
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
		return 0;
	}
	newLayer->layerID = iOCT_layerCounter;				// store own position
	iOCT_layerPool[iOCT_layerCounter] = newLayer;		// store entitySet

	iOCT_layerCounter += 1;
	return newLayer->layerID;
}

void iOCT_layer_initialize() {
	memset(iOCT_layerPool, iOCT_NO_RENDEREROBJECT, sizeof(iOCT_layerPool));
	printf("Layer pool zeroed out\n");
}

iOCT_rendererObjectHandle iOCT_rendererObject_locate(OCT_entityHandle entity, OCT_componentTypes componentType) {
	return iOCT_rendererObjectMap[entity.entitySetID][entity.entityID][componentType];
}