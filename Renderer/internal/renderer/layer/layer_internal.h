#pragma once
#include "standards/rendererStandards_internal.h"

#include "renderer/rendererObject/rendererObject_internal.h"
#include "OCT_Math.h"

#define iOCT_LAYER_MAX 64

typedef size_t iOCT_layerID;

typedef struct iOCT_layer {
	iOCT_layerID layerID;

	OCT_counter rendererObjectCounter;
	iOCT_rendererObject rendererObjectPool[1024];	// NOTE_URGENT_HARDCODED

} iOCT_layer;

extern iOCT_layer* iOCT_layerPool[iOCT_LAYER_MAX];

typedef struct {
	iOCT_rendererObjectID rendererObjectID;
	iOCT_layerID layerID;
} iOCT_rendererObjectHandle;

extern iOCT_rendererObjectHandle iOCT_rendererObjectMap[64][1024][OCT_componentsTotal];

iOCT_layer* iOCT_layer_get(iOCT_layerID layerID);
iOCT_layerID iOCT_layer_new();
void iOCT_layer_initialize();

iOCT_rendererObjectHandle iOCT_rendererObject_locate(OCT_entityHandle entity, OCT_componentTypes componentType);




