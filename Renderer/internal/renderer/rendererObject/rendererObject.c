#include "renderer/rendererObject/rendererObject.h"
#include "renderer/types_internal.h"

#include "OCT_ECS.h"

#include "renderer/layer/layer_internal.h"

void iOCT_rendererObject_getTransforms(iOCT_rendererObject obj) {
	
}

OCT_handle iOCT_rendererObject_add(iOCT_layer* layer, OCT_handle engineHandle, OCT_handle transform) {
	OCT_ID newID;
	OCT_index newIndex;
	iOCT_rendererObject* newObj = { 0 };

	newObj = iOCT_pool_addEntry(&layer->pool, &newIndex);
	newID = iOCT_IDMap_register(&layer->IDMap, newIndex);

	newObj->engineHandle = engineHandle;
	newObj->transformHandle = transform;
	newObj->color = (OCT_vec4){ 1.0, 1.0, 1.0, 1.0 };
	newObj->uvRect = (OCT_vec4){ 0.0, 0.0, 1.0, 1.0 };

	OCT_handle newHandle = {
		.subsystem = OCT_subsystem_renderer,
		.objectID = newID,
		.containerID = layer->layerID,
		.type = OCT_handle_rendererObject
	};
	return newHandle;
}