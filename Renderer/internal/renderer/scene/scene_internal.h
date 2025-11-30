#pragma once
#include "renderer/scene/scene.h"
#include "standards/rendererStandards_internal.h"

#include "renderer/rendererObject/rendererObject_internal.h"

typedef struct iOCT_scene {
	counter rendererObjectCounter;
	rendererObject rendererObjectPool[MAX_RENDEREROBJECTS];
} iOCT_scene;

rendererObject* rendererObject_getPool();
counter* rendererObject_getCounter();
rendererObject* rendererObject_get(OCT_rendererObjectID OCT_rendererObjectID);


