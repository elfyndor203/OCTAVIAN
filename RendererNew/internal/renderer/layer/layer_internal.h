#pragma once
#include "standards/rendererStandards_internal.h"

#include "OCT_Math.h"

#define iOCT_LAYER_MAX 64

typedef size_t iOCT_layerID;

typedef struct iOCT_layer {
	iOCT_layerID layerID;

	OCT_counter rendererObjectCounter;
	iOCT_rendererObject rendererObjectPool[iOCT_MAX_RENDEREROBJECTS];

} iOCT_layer;

iOCT_layer* iOCT_layerPool[iOCT_LAYER_MAX]; /// pointers