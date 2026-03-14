#include "renderer/rendererObject/rendererObject.h"
#include "rendererObject_internal.h"
#include "renderer/layer/layer_internal.h"

void OCT_render(OCT_entityHandle entity, OCT_types componentType) {
	iOCT_rendererObjectHandle rendererHandle = iOCT_rendererObject_locate(entity, componentType);
	iOCT_render(rendererHandle.rendererObjectID, rendererHandle.layerID);
}