#pragma once
#include "types.h"

typedef enum {
	OCT_subsystem_threshold = 1000,

	OCT_subsystem_ECS,
	OCT_subsystem_renderer,
	OCT_subsystem_resources
} OCT_subsystemList;

typedef enum {
	OCT_handle_null = 0,

	OCT_handle_context,
	OCT_handle_entity,
	OCT_handle_transform2D,
	OCT_handle_hitBox2D,
	OCT_handle_sprite,

	OCT_handle_layer,
	OCT_handle_rendererObject,
	
	OCT_handle_image,
	OCT_handle_mesh
} OCT_handleType;

struct OCT_handle {
	OCT_ID ownerID;
	OCT_ID objectID;
};

extern const OCT_ID OCT_errorID;
extern OCT_handle _OCT_active;
extern OCT_handle _OCT_errorHandle;

