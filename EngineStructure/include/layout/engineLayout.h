#pragma once
#include "types.h"

typedef enum {
	OCT_subsystem_ECS,
	OCT_subsystem_renderer,
	OCT_subsystem_resources,
	OCT_subsystem_window,
	OCT_subsystem_input,

	OCT_subsystem_count
} OCT_subsystemList;	// to add a new subsystem, add it here and give it an inbox and eventbox in CORModule_internal.h, then add it to the messageBox getter in messaging.c

typedef enum {
	OCT_handle_null = 0,

	OCT_handle_entityContext,
	OCT_handle_entity,
	OCT_handle_transform2D,
	OCT_handle_hitBox2D,
	OCT_handle_sprite2D,

	OCT_handle_layer,
	
	OCT_handle_image,
	OCT_handle_mesh,

	OCT_handle_window
} OCT_handleType;

struct OCT_handle {
	OCT_ID subsystem;
	OCT_ID containerID;
	OCT_ID objectID;
	OCT_handleType type;
};

extern const OCT_ID OCT_errorID;
extern OCT_handle _OCT_active;
extern OCT_handle _OCT_errorHandle;

