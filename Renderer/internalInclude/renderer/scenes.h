#pragma once
#include "myStandards.h"

#include "renderer/rendererObject.h"

typedef struct {
	counter rendererObjectCounter;
	rendererObject rendererObjectPool[MAX_RENDEREROBJECTS];
} scene;

rendererObject* getRendererObjectPool();
counter* getRendererObjectCounter();
rendererObject* getRendererObject(rendererObjectIndex rendererObjectIndex);


