#include "_REN_input/messageHandling_internal.h"

#include <stdio.h>
#include "OCT_Messaging.h"
#include "bufferGeneration_internal.h"
#include "renderer/rendererObject/rendererObject_internal.h"
#include "shaders/shader/shader_internal.h"

void iOCT_handleMessages(void) {
	while (_OCT_queryMessage(_OCT_Renderer).instruction != _OCT_empty) {
		_OCT_message newMessage = _OCT_queryMessage(_OCT_Renderer);
		OCT_entityHandle entity = newMessage.entity;
		_OCT_messageTypes instruction = newMessage.instruction;
		iOCT_layerID layer = (iOCT_layerID)newMessage.parameter;
		//iOCT_rendererObject* rendererObject = iOCT_rendererObject_get(entity.rendererObjectID, entity.layerID); //	NOTE_FIX

		switch(instruction) {
		case _OCT_hitBox2D_add:
			;
			iOCT_rendererObject* rendererObject = iOCT_rendererObject_get(iOCT_rendererObject_new(entity, layer, iOCT_shaderProgramList[shader_debug], true), layer);
			iOCT_glInfo glInfo = iOCT_generateBuffers_debug(entity);
			rendererObject->debug_VAO = glInfo.VAO;
			rendererObject->debug_VBO = glInfo.VBO;
			rendererObject->debug_EBO = glInfo.EBO;
			printf("Handled debug add");
		}
	}
}