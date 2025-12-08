#pragma once
#include "stddef.h"
#include <stdbool.h>
#include <stdint.h>

#define iOCT_MAX_MESSAGES 1024

typedef size_t iOCT_messageCounter;

typedef enum {
	_OCT_update,
	_OCT_update_debug,
	_OCT_add,
	_OCT_add_debug,
	_OCT_delete,

	_OCT_empty = SIZE_MAX
} _OCT_messageTypes;

typedef enum {
	_OCT_ECS,
	_OCT_Renderer
} _OCT_subsystemList;

typedef size_t OCT_entitySetID;		// ONLY LINKED DATA HERE
typedef size_t OCT_entityID;
typedef size_t OCT_layerID; 
typedef size_t OCT_rendererObjectID;
typedef struct {
	OCT_entitySetID entitySetID;
	OCT_entityID entityID;
	OCT_layerID layerID;
	OCT_rendererObjectID rendererObjectID;
} OCT_entityHandle;

typedef struct {
	OCT_entityHandle entity;
	_OCT_messageTypes message;
} _OCT_message;

extern _OCT_message _OCT_messageQueue_empty;

_OCT_message _OCT_queryMessage(_OCT_subsystemList subsystem);

bool _OCT_sendMessage(_OCT_subsystemList subsystem, OCT_entityHandle entity, _OCT_messageTypes message);
