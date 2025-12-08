#include "renderer/rendererObject/rendererObject.h"
#include "rendererObject_internal.h"

void OCT_render_debug(OCT_entityHandle entity) {
	iOCT_render_debug(entity, entity.layerID);
}