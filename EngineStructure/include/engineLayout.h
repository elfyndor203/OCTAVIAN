#pragma once

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

typedef uint64_t OCT_ID;

typedef struct {
	OCT_ID entityContextID;
	OCT_ID entityID;
} OCT_entityHandle;

extern const OCT_ID OCT_errorID;
extern OCT_entityHandle _OCT_active;
extern OCT_entityHandle _OCT_errorHandle;