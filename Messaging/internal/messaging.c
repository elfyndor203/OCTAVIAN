#include "messaging.h"
#include "messaging_internal.h"

#include <stdbool.h>
#include <stdint.h>
#include "OCT_Errors.h"

iOCT_messageCounter iOCT_REN_head = 0;
iOCT_messageCounter iOCT_REN_tail = 0;

_OCT_message _OCT_messageQueue_empty = { SIZE_MAX, _OCT_empty };

static bool iOCT_queueEmpty(iOCT_messageCounter head, iOCT_messageCounter tail) {
	return head == tail; // next write == next read, caught up
}

static bool iOCT_queueFull(iOCT_messageCounter head, iOCT_messageCounter tail) {
	return (head + 1) % iOCT_MAX_MESSAGES == tail;										// this is true when the next message would overwrite the message about to be read
}

bool _OCT_sendMessage(_OCT_subsystemList recipient, OCT_entityHandle entity, _OCT_messageTypes message) {
	_OCT_message messageToSend = { entity, message };

	switch (recipient) {
	case _OCT_Renderer:
		if (iOCT_queueFull(iOCT_REN_head, iOCT_REN_tail)) {
			OCT_logError(EXIT_RENDERER_MESSAGES_OVERLOADED);
			return false;
		}
		iOCT_REN_messageQueue[iOCT_REN_head] = messageToSend;
		iOCT_REN_head = (iOCT_REN_head + 1) % iOCT_MAX_MESSAGES;	// if at MAX, reset to 0, otherwise add 1

		printf("Sent message to renderer");
		return true;
		break;
	default:
		OCT_logError(EXIT_NOT_YET_IMPLEMENTED);
		return false;
	}
}

_OCT_message _OCT_queryMessage(_OCT_subsystemList subsystem) {
	_OCT_message messageToHandle = _OCT_messageQueue_empty;

	switch (subsystem) {
	case _OCT_Renderer:
		if (iOCT_queueEmpty(iOCT_REN_head, iOCT_REN_tail)) {
			return _OCT_messageQueue_empty;
		}
		messageToHandle = iOCT_REN_messageQueue[iOCT_REN_tail];
		iOCT_REN_tail = (iOCT_REN_tail + 1) % iOCT_MAX_MESSAGES;	// wraparound
		break;
	default:
		OCT_logError(EXIT_NOT_YET_IMPLEMENTED);
	}
	return messageToHandle;
}
