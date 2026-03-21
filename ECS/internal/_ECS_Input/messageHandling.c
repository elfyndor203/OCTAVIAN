#include "messageHandling_internal.h"
#include <stdio.h>

#include "OCT_ECS.h"
#include "ECS/entity/entity_internal.h"

bool activeMoving = false;

void iOCT_handleECSMessages(void) {
	cOCT_message newMessage = _OCT_queryMessage(OCT_subsystem_ECS);

	//printf("DO: %d", newMessage.instruction);
	while (newMessage.instruction != _OCT_messageQueue_empty.instruction) {
		cOCT_messageTypes instruction = newMessage.instruction;
		float value1 = newMessage.parameter1;
		float value2 = newMessage.parameter2;
		newMessage = _OCT_queryMessage(OCT_subsystem_ECS);

		switch (instruction) {
		case _OCT_position2D_move:
			activeMoving = true;
//			OCT_transform2D_moveBy(testActiveEntity, value1, value2);
			printf("Moved entity %zu by %f, %f", testActiveEntity.objectID, value1, value2);
			break;
		case _OCT_position2D_stop:
			activeMoving = false;
			break;
		}

	}
	//printf("Cleared messages\n");
}
