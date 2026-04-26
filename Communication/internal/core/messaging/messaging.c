#include "messaging_internal.h"
#include "messaging/messaging_core.h"
#include "core/types_internal.h"
#include "types_core.h"

#include <stdio.h>
#include <string.h>

#include "module/COMModule_internal.h"

static bool iOCT_queueEmpty(cOCT_messageBox* box);
static bool iOCT_queueFull(cOCT_messageBox* box);
static cOCT_messageBox* iOCT_messageBox_get(OCT_subsystemList recipient, cOCT_messageBoxType boxType);

static cOCT_message iOCT_emptyMessage = {
	.messageType = cOCT_MSG_ALLCLEAR
};

bool cOCT_message_push(OCT_subsystemList recipient, cOCT_message message, cOCT_messageBoxType boxType) {
	cOCT_messageBox* box = iOCT_messageBox_get(recipient, boxType);

	if (box == NULL || iOCT_queueFull(box)) {
		return false;
	}

	box->queue[box->head] = message;
	//printf("Pushing MSG %d to INBOX %d, at HEAD %zu\n", message.messageType, inbox->owner, inbox->head);
	box->head = (box->head + 1) % cOCT_MESSAGES_MAX;
	box->count++;
	return true;
}

cOCT_message cOCT_message_pop(OCT_subsystemList self) {
	cOCT_messageBox* inbox = iOCT_messageBox_get(self, cOCT_INBOX);
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

cOCT_message cOCT_event_read(OCT_subsystemList eventBox, OCT_index num) {
	cOCT_messageBox* box = iOCT_messageBox_get(eventBox, cOCT_EVENTBOX);
	cOCT_message* array = (cOCT_message*)box->queue;
	cOCT_message msg;
	if (num >= box->count) {
		msg.messageType = cOCT_MSG_ALLCLEAR;
		return msg;
	}

	msg = array[(box->tail + num) % cOCT_MESSAGES_MAX];
	return msg;
}

void iOCT_eventBox_clear(cOCT_messageBox* eventBox) {
	memset(&eventBox->queue, 0, sizeof(cOCT_message) * cOCT_MESSAGES_MAX);
	eventBox->count = 0;
	eventBox->head = 0;
	eventBox->tail = 0;
}
#pragma region helpers
static bool iOCT_queueEmpty(cOCT_messageBox* box) {
	return box->head == box->tail;
}

static bool iOCT_queueFull(cOCT_messageBox* box) {
	return (box->head + 1) % cOCT_MESSAGES_MAX == box->tail; // this is true when the next message would overwrite the message about to be read
}

static cOCT_messageBox* iOCT_messageBox_get(OCT_subsystemList recipient, cOCT_messageBoxType boxType) {
	cOCT_messageBox* box;

	if (boxType == cOCT_INBOX) {
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
		case OCT_subsystem_physics:
			box = &iOCT_COMModule_instance.inbox_PHY;
			break;
		default:
			printf("Box DNE\n");
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
		case OCT_subsystem_physics:
			box = &iOCT_COMModule_instance.eventBox_PHY;
			break;
		default:
			printf("Box DNE\n");
			return NULL;
		}
	}
	return box;
}
#pragma endregion