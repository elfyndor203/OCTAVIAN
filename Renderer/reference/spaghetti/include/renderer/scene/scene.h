#pragma once
#include "standards/rendererStandards.h"

#include "renderer/rendererObject/rendererObject.h"

typedef struct scene scene;

rendererObject* OCT_rendererObject_getPool();
counter* OCT_rendererObject_getCounter();
rendererObject* OCT_rendererObject_get(OCT_rendererObjectID OCT_rendererObjectID);
