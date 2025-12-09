#include "messageHandling_internal.h"

#include "OCT_ECS.h"
#include "ECS/entity/entity_internal.h"

bool activeMoving = false;

void iOCT_handleECSMessages(void) {
	_OCT_message newMessage = _OCT_queryMessage(_OCT_ECS);

	//printf("DO: %d", newMessage.instruction);
	while (newMessage.instruction != _OCT_messageQueue_empty.instruction) {
		_OCT_messageTypes instruction = newMessage.instruction;
		float value1 = newMessage.parameter1;
		float value2 = newMessage.parameter2;
		newMessage = _OCT_queryMessage(_OCT_ECS);

		switch (instruction) {
		case _OCT_position2D_move:
			activeMoving = true;
			OCT_position2D_move(testActiveEntity, value1, value2);
			printf("Moved entity %zu by %f, %f", testActiveEntity.entityID, value1, value2);
			break;
		case _OCT_position2D_stop:
			activeMoving = false;
			break;
		}

	}
	//printf("Cleared messages\n");
}
