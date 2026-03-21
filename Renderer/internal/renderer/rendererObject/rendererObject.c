#include "renderer/rendererObject/rendererObject_internal.h"
#include "renderer/types_internal.h"

#include "OCT_ECS.h"

#include "renderer/layer/layer_internal.h"

void iOCT_rendererObject_getTransforms(iOCT_rendererObject obj) {
	
}

OCT_handle iOCT_rendererObject_add(iOCT_layer* layer, OCT_vec4 color, OCT_vec4 uv, OCT_handle engineHandle, OCT_handle transform) {
	OCT_ID newID;
	OCT_index newIndex;
	iOCT_rendererObject* newObj = { 0 };

	newObj = cOCT_pool_addEntry(&layer->pool, &newIndex);
	newID = cOCT_IDMap_register(&layer->IDMap, newIndex);

	newObj->engineHandle = engineHandle;
	newObj->transformHandle = transform;
	newObj->color = color;
	newObj->uvRect = uv;

	OCT_handle newHandle = {
		.subsystem = OCT_subsystem_renderer,
		.objectID = newID,
		.containerID = layer->layerID,
		.type = OCT_handle_rendererObject
	};
	return newHandle;
}