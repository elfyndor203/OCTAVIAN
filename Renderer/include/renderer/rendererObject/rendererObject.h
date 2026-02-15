#pragma once
#include "standards/rendererStandards.h"

typedef size_t OCT_layerID;
// void OCT_renderObject(OCT_entityHandle entityHandle);
//void OCT_render_debug(OCT_entityHandle entity);

void OCT_render(OCT_entityHandle entity, OCT_types componentType);