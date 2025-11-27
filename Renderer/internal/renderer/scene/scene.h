#pragma once
#include "standards/rendererStandards.h"

#include "renderer/rendererObject/rendererObject.h"

typedef struct {
	counter rendererObjectCounter;
	rendererObject rendererObjectPool[MAX_RENDEREROBJECTS];
} scene;

rendererObject* rendererObject_getPool();
counter* rendererObject_getCounter();
rendererObject* rendererObject_get(rendererObjectIndex rendererObjectIndex);


