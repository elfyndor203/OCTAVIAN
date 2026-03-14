#pragma once
#include "renderer/scene/scene.h"
#include "standards/rendererStandards_internal.h"

#include "renderer/rendererObject/rendererObject_internal.h"

typedef struct scene {
	counter rendererObjectCounter;
	rendererObject rendererObjectPool[MAX_RENDEREROBJECTS];
} scene;

rendererObject* rendererObject_getPool();
counter* rendererObject_getCounter();
rendererObject* rendererObject_get(OCT_rendererObjectID OCT_rendererObjectID);


