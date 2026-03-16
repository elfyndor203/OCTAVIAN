#pragma once
#include "types.h"

typedef enum {
	OCT_subsystem_ECS = 1000,
	OCT_subsystem_renderer = 2000,
	OCT_subsystem_resources = 3000
} OCT_subsystemList;

typedef struct OCT_engineHandle {
	OCT_ID ownerID;
	OCT_ID objectID;
} OCT_handle;

extern const OCT_ID OCT_errorID;
extern OCT_handle _OCT_active;
extern OCT_handle _OCT_errorHandle;