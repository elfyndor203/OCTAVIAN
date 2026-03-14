#pragma once
#include "types.h"

typedef enum {
	_OCT_ECS = 1000,
	_OCT_Renderer = 2000
} _OCT_subsystemList;

typedef enum {
	OCT_typeEntity,		

	OCT_typeComponentTransform2D,
	OCT_typeComponentHitBox2D,

	OCT_typesTotal
} OCT_types; // IF UPDATED, POOLS.C MUST ALSO BE UPDATED TO GET THE STRUCT SIZE

typedef struct OCT_engineHandle {
	OCT_ID contextID;
	OCT_ID objectID;
} OCT_engineHandle;

extern const OCT_ID OCT_errorID;
extern OCT_engineHandle _OCT_active;
extern OCT_engineHandle _OCT_errorHandle;