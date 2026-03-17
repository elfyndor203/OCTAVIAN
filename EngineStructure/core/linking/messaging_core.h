#pragma once
#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "layout/engineLayout.h"

#define iOCT_MAX_MESSAGES 1024

typedef size_t iOCT_messageCounter;

typedef enum {
	_OCT_sprite_add,
	_OCT_sprite_update,
	_OCT_sprite_delete,

	_OCT_hitBox2D_add,
	_OCT_hitBox2D_update,

	_OCT_position2D_move,
	_OCT_position2D_stop,
	_OCT_empty = SIZE_MAX
} _OCT_messageTypes;

typedef struct {
	OCT_handle entity;
	_OCT_messageTypes instruction;
	float parameter1;
	float parameter2;
} _OCT_message;

extern _OCT_message _OCT_messageQueue_empty;

extern _OCT_message iOCT_REN_messageQueue[iOCT_MAX_MESSAGES];
extern _OCT_message iOCT_ECS_messageQueue[iOCT_MAX_MESSAGES];

_OCT_message _OCT_queryMessage(OCT_subsystemList subsystem);

bool _OCT_sendMessage(OCT_subsystemList recipient, OCT_handle entity, _OCT_messageTypes instruction, float parameter1, float parameter2);

