#include "sprite2D_internal.h"
#include "ECS/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"
#include <assert.h>
#include <stdbool.h>

#include "ECS/entityContext/entityContext_internal.h"

OCT_handle OCT_sprite2D_add(OCT_handle entity, OCT_handle layer, OCT_vec4 color, OCT_vec4 uv) {
	assert(entity.type == OCT_handle_entity && layer.type == OCT_handle_layer);
	iOCT_entityContext* context = iOCT_entityContext_get(entity.containerID);
	OCT_ID entityID = entity.objectID;

	OCT_ID spriteID = iOCT_sprite2D_add(context, entityID, entity, layer, color, uv);

	OCT_handle spriteHandle = {
		.subsystem = OCT_subsystem_ECS,
		.containerID = context->contextID,
		.objectID = spriteID,
		.type = OCT_handle_sprite2D
	};

	return spriteHandle;
}
OCT_ID iOCT_sprite2D_add(iOCT_entityContext* context, OCT_ID entityID, OCT_handle entityHandle, OCT_handle layer, OCT_vec4 color, OCT_vec4 uv) {
	OCT_ID newID;
	OCT_index newIndex;
	iOCT_sprite2D* newSprite;

	newSprite = (iOCT_sprite2D*)cOCT_pool_addEntry(iOCT_pool_get(context, OCT_ECSType_sprite2D), &newIndex);
	newID = cOCT_IDMap_register(&context->IDMap, newIndex);

	newSprite->uv = uv;
	newSprite->visible = true;

	OCT_handle transformHandle = {
		.subsystem = OCT_subsystem_ECS,
		.containerID = context->contextID,
		.objectID = iOCT_entity_get(context, entityID)->transformID,
		.type = OCT_handle_transform2D
	};

	cOCT_message renMsg = {
		.messageType = cOCT_MSG_RENDERABLE_NEW,
		.renderable_new = {
			.layerHandle = layer,
			.entityHandle = entityHandle,
			.transformHandle = transformHandle,
			.color = color,
			.uv = uv
		}
	};
	cOCT_message_push(OCT_subsystem_renderer, renMsg);
	return newID;
}