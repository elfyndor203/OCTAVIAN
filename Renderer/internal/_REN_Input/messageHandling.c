#include "_REN_input/messageHandling_internal.h"

#include <stdio.h>
#include "OCT_Messaging.h"
#include "bufferGeneration_internal.h"
#include "renderer/rendererObject/rendererObject_internal.h"

void iOCT_handleMessages(void) {
	while (_OCT_queryMessage(_OCT_Renderer).message != _OCT_empty) {
		_OCT_message newMessage = _OCT_queryMessage(_OCT_Renderer);
		OCT_entityHandle entity = newMessage.entity;
		_OCT_messageTypes message = newMessage.message;

		iOCT_rendererObject* rendererObject = iOCT_rendererObject_get(entity.rendererObjectID, entity.layerID); //	NOTE_FIX

		switch(message) {
		case _OCT_add_debug:
			;
			iOCT_glInfo glInfo = iOCT_generateBuffers_debug(entity, entity.layerID);
			rendererObject->debug_VAO = glInfo.VAO;
			rendererObject->debug_VBO = glInfo.VBO;
			rendererObject->debug_EBO = glInfo.EBO;
			printf("Handled debug add");
		}
	}
}