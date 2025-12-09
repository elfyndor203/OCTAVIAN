#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "engineLayout.h"

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
	OCT_entityHandle entity;
	_OCT_messageTypes instruction;
	uint64_t parameter;
} _OCT_message;

extern _OCT_message _OCT_messageQueue_empty;

_OCT_message _OCT_queryMessage(_OCT_subsystemList subsystem);

bool _OCT_sendMessage(_OCT_subsystemList recipient, OCT_entityHandle entity, _OCT_messageTypes instruction, uint64_t parameter);
