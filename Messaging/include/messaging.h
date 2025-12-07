#pragma once
#include "stddef.h"
#include <stdbool.h>

#define iOCT_MAX_MESSAGES 1024

typedef size_t iOCT_messageCounter;

typedef enum {
	_OCT_update,
	_OCT_add,
	_OCT_delete
} _OCT_messageTypes;

typedef enum {
	_OCT_ECS,
	_OCT_Renderer
} _OCT_subsystemList;

typedef struct {
	OCT_entityHandle entity;
	_OCT_messageTypes message;
} _OCT_message;

typedef size_t OCT_entitySetID;
typedef size_t OCT_entityID;

typedef struct {
	OCT_entitySetID entitySetID;
	OCT_entityID entityID;
} OCT_entityHandle;

bool _OCT_sendMessage(_OCT_subsystemList subsystem, OCT_entityHandle entity, _OCT_messageTypes message);
_OCT_message _OCT_queryMessage(_OCT_subsystemList subsystem);
