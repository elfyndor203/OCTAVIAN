#include "module/RESModule_internal.h"
#include "resources/types_internal.h"

#include "cOCT_Communication.h"
#include "cOCT_EngineStructure.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void iOCT_RESModule_handleMSGs() {
	cOCT_message msg;

	msg = cOCT_message_pop(OCT_subsystem_resources);
	while (msg.messageType != cOCT_MSG_ALLCLEAR) {
		switch (msg.messageType) {
		case cOCT_MSG_TEXTURE_DONE:
			printf("Freeing resource %p\n", msg.texture_done.pixels);
			if (msg.texture_done.pixels) {
				free(msg.texture_done.pixels);
			}
			break;
		}

		msg = cOCT_message_pop(OCT_subsystem_resources);

	}
}