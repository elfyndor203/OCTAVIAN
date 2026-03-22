#include "sprite2D_internal.h"
#include "ECS/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"
#include <assert.h>
#include <stdbool.h>

#include "ECS/entityContext/entityContext_internal.h"

iOCT_sprite2D* iOCT_sprite2D_get(iOCT_entityContext* context, OCT_ID spriteID) {
	return (iOCT_sprite2D*)iOCT_getByID(context, spriteID, OCT_ECSType_sprite2D);
}

OCT_handle OCT_sprite2D_add(OCT_handle entity, OCT_handle layer, OCT_vec4 color, OCT_vec4 uv, OCT_vec2 dimensions) {
	assert(entity.type == OCT_handle_entity && layer.type == OCT_handle_layer);
	iOCT_entityContext* context = iOCT_entityContext_get(entity.containerID);
	OCT_ID entityID = entity.objectID;

	OCT_ID spriteID = iOCT_sprite2D_add(context, entityID, entity, layer, color, uv, dimensions);

	OCT_handle spriteHandle = {
		.subsystem = OCT_subsystem_ECS,
		.containerID = context->contextID,
		.objectID = spriteID,
		.type = OCT_handle_sprite2D
	};

	return spriteHandle;
}
OCT_ID iOCT_sprite2D_add(iOCT_entityContext* context, OCT_ID entityID, OCT_handle entityHandle, OCT_handle layer, OCT_vec4 color, OCT_vec4 uv, OCT_vec2 dimensions) {
	OCT_ID newID;
	OCT_index newIndex;
	iOCT_sprite2D* newSprite;

	newSprite = (iOCT_sprite2D*)cOCT_pool_addEntry(iOCT_pool_get(context, OCT_ECSType_sprite2D), &newIndex);
	newID = cOCT_IDMap_register(&context->IDMap, newIndex);

	newSprite->uv = uv;
	newSprite->visible = true;
	newSprite->color = color;
	newSprite->dimensions = dimensions;

	OCT_handle transformHandle = {
		.subsystem = OCT_subsystem_ECS,
		.containerID = context->contextID,
		.objectID = iOCT_entity_get(context, entityID)->transformID,
		.type = OCT_handle_transform2D
	};
	OCT_handle spriteHandle = {
	.subsystem = OCT_subsystem_ECS,
	.containerID = context->contextID,
	.objectID = newID,
	.type = OCT_handle_sprite2D
	};

	cOCT_message renMsg = {
		.messageType = cOCT_MSG_RENDERABLE_NEW,
		.renderable_new = {
			.layerHandle = layer,
			.entityHandle = entityHandle,
			.transformHandle = transformHandle,
			.renderableHandle = spriteHandle
		}
	};
	cOCT_message_push(OCT_subsystem_renderer, renMsg);
	return newID;
}

#pragma region cross-module requests
OCT_vec4 _OCT_sprite2D_getUV(OCT_handle spriteHandle) {
	iOCT_entityContext* context = iOCT_entityContext_get(spriteHandle.containerID);
	return iOCT_sprite2D_get(context, spriteHandle.objectID)->uv;
}
OCT_vec4 _OCT_sprite2D_getColor(OCT_handle spriteHandle) {
	iOCT_entityContext* context = iOCT_entityContext_get(spriteHandle.containerID);
	return iOCT_sprite2D_get(context, spriteHandle.objectID)->color;
}
OCT_vec2 _OCT_sprite2D_getDimensions(OCT_handle spriteHandle) {
	iOCT_entityContext* context = iOCT_entityContext_get(spriteHandle.containerID);
	return iOCT_sprite2D_get(context, spriteHandle.objectID)->dimensions;
}
#pragma endregion