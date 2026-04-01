#include "messaging_internal.h"
#include "messaging/messaging_core.h"
#include "core/types_internal.h"
#include "types_core.h"

#include "module/COMModule_internal.h"

static bool iOCT_queueEmpty(cOCT_messageBox* box);
static bool iOCT_queueFull(cOCT_messageBox* box);
static cOCT_messageBox* iOCT_messageBox_get(OCT_subsystemList recipient, int boxType);

static cOCT_message iOCT_emptyMessage = {
	.messageType = cOCT_MSG_ALLCLEAR
};

bool cOCT_message_push(OCT_subsystemList recipient, cOCT_message message) {
	cOCT_messageBox* inbox = iOCT_messageBox_get(recipient, iOCT_INBOX);

	if (inbox == NULL || iOCT_queueFull(inbox)) {
		return false;
	}

	inbox->queue[inbox->head] = message;
	//printf("Pushing MSG %d to INBOX %d, at HEAD %zu\n", message.messageType, inbox->owner, inbox->head);
	inbox->head = (inbox->head + 1) % cOCT_MESSAGES_MAX;

	return true;
}

cOCT_message cOCT_message_pop(OCT_subsystemList self) {
	cOCT_messageBox* inbox = iOCT_messageBox_get(self, iOCT_INBOX);
	cOCT_message msg;

	if (iOCT_queueEmpty(inbox)) {
		return iOCT_emptyMessage;
	}
	//printf("Message available\n");
	msg = inbox->queue[inbox->tail];
	//printf("Popping MSG %d from INBOX %d, at TAIL %zu\n", msg.messageType, inbox->owner, inbox->tail);
	inbox->tail = (inbox->tail + 1) % cOCT_MESSAGES_MAX;	// wraparound

	return msg;
}

#pragma region helpers
static bool iOCT_queueEmpty(cOCT_messageBox* box) {
	return box->head == box->tail;
}

static bool iOCT_queueFull(cOCT_messageBox* box) {
	return (box->head + 1) % cOCT_MESSAGES_MAX == box->tail; // this is true when the next message would overwrite the message about to be read
}

static cOCT_messageBox* iOCT_messageBox_get(OCT_subsystemList recipient, int boxType) {
	cOCT_messageBox* box;

	if (boxType == iOCT_INBOX) {
		switch (recipient) {
		case OCT_subsystem_ECS:
			box = &iOCT_COMModule_instance.inbox_ECS;
			break;
		case OCT_subsystem_resources:
			box = &iOCT_COMModule_instance.inbox_RES;
			break;
		case OCT_subsystem_renderer:
			box = &iOCT_COMModule_instance.inbox_REN;
			break;
		case OCT_subsystem_window:
			box = &iOCT_COMModule_instance.inbox_WDW;
			break;
		case OCT_subsystem_input:
			box = &iOCT_COMModule_instance.inbox_INP;
			break;
		default:
			return NULL;
		}
	}
	else {
		switch (recipient) {
		case OCT_subsystem_ECS:
			box = &iOCT_COMModule_instance.eventBox_ECS;
			break;
		case OCT_subsystem_resources:
			box = &iOCT_COMModule_instance.eventBox_RES;
			break;
		case OCT_subsystem_renderer:
			box = &iOCT_COMModule_instance.eventBox_REN;
			break;
		case OCT_subsystem_window:
			box = &iOCT_COMModule_instance.eventBox_WDW;
			break;
		default:
			return NULL;
		}
	}
	return box;
}
#pragma endregion