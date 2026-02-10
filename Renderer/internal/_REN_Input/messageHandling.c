#include "_REN_input/messageHandling_internal.h"

#include <stdio.h>
#include "OCT_EngineStructure.h"
#include "bufferGeneration_internal.h"
#include "renderer/rendererObject/rendererObject_internal.h"
#include "shaders/shader/shader_internal.h"

void iOCT_handleRendererMessages(void) {
	_OCT_message newMessage = _OCT_queryMessage(_OCT_Renderer);
	while (newMessage.instruction != _OCT_messageQueue_empty.instruction) {
		OCT_entityHandle entity = newMessage.entity;
		_OCT_messageTypes instruction = newMessage.instruction;
		iOCT_layerID layer = (iOCT_layerID)newMessage.parameter1;
		newMessage = _OCT_queryMessage(_OCT_Renderer);
		//iOCT_rendererObject* rendererObject = iOCT_rendererObject_get(entity.rendererObjectID, entity.layerID); //	NOTE_FIX
		switch (instruction) {
		case _OCT_hitBox2D_add:
			iOCT_rendererObject_new(entity, layer, OCT_componentHitBox2D, iOCT_shaderProgramList[shader_debug], true);
			//printf("Handled hitbox2D creation\n");
			break;
		case _OCT_hitBox2D_update:
			iOCT_updateVertexBuffer(entity, OCT_componentHitBox2D);
			//printf("Handled hitbox2D update\n");
			break;
		}
	}
	//printf("Cleared messages\n");
}