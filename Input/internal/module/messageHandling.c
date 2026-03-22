
#include "cOCT_EngineStructure.h"
#include <assert.h>
#include <stdio.h>

void iOCT_INPModule_handleMSGs() {
	cOCT_message msg = cOCT_message_pop(OCT_subsystem_input);

	while (msg.messageType != cOCT_MSG_ALLCLEAR) {
		assert(msg.messageType == cOCT_MSG_BUTTON_DOWN || msg.messageType == cOCT_MSG_BUTTON_UP);
		if (msg.messageType == cOCT_MSG_BUTTON_DOWN) {
			printf("Key: %c pressed \n", msg.button_event.button);
		}
		else {
			printf("Key: %c released \n", msg.button_event.button);
		}

		msg = cOCT_message_pop(OCT_subsystem_input);
	}
}