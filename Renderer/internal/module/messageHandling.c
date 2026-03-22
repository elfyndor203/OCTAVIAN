#include "module/RENModule_internal.h"
#include "renderer/types_internal.h"

#include "cOCT_EngineStructure.h"
#include <assert.h>
#include <glad/glad.h>

#include "renderer/layer/layer_internal.h"
#include "renderer/texture/texture_internal.h"
#include "renderer/rendererObject/rendererObject_internal.h"

void iOCT_RENModule_handleMSGs() {
	cOCT_message msg;

	msg = cOCT_message_pop(OCT_subsystem_renderer);
	while (msg.messageType != cOCT_MSG_ALLCLEAR) {
		switch (msg.messageType) {
		case cOCT_MSG_TEXTURE_LOAD: {
			GLuint texture = iOCT_texture2D_load(msg.texture_load.pixels, msg.texture_load.width, msg.texture_load.height, msg.texture_load.texHandle);

			cOCT_message doneMsg = {
				.messageType = cOCT_MSG_TEXTURE_DONE,
				.texture_done = {
					.rendererRef = texture,
					.texHandle = msg.texture_load.texHandle
				}

			};
			cOCT_message_push(OCT_subsystem_resources, doneMsg);
			break;
		}
		case cOCT_MSG_RENDERABLE_NEW: {
			iOCT_layer* layer = iOCT_layer_get(msg.renderable_new.layerHandle.objectID);
			iOCT_rendererObject_add(layer, msg.renderable_new.entityHandle, msg.renderable_new.transformHandle, msg.renderable_new.renderableHandle);
			break;
		}
		default:
			assert(false && "Message unhandled by REN");
		}

		msg = cOCT_message_pop(OCT_subsystem_renderer);
	}
}