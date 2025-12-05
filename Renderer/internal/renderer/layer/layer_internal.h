#pragma once
#include "standards/rendererStandards_internal.h"

#include "renderer/rendererObject/rendererObject_internal.h"

#define iOCT_LAYER_MAX 64

typedef size_t iOCT_layerID;

typedef struct iOCT_layer {
	iOCT_layerID layerID;

	OCT_counter rendererObjectCounter;
	iOCT_rendererObject rendererObjectPool[iOCT_MAX_RENDEREROBJECTS];

	iOCT_rendererObjectID entityMap[iOCT_LAYER_MAX][iOCT_MAX_RENDEREROBJECTS]; // indexes rendererObjects by their gameObjectHandle
} iOCT_layer;

iOCT_layer* iOCT_layerPool[iOCT_LAYER_MAX]; /// pointers

iOCT_layer* iOCT_layer_get(iOCT_layerID layerID);
iOCT_layerID iOCT_layer_new();
void iOCT_layer_initialize();



