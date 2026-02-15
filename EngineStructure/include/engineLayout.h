#pragma once

typedef enum {
	_OCT_ECS = 1000,
	_OCT_Renderer = 2000
} _OCT_subsystemList;

typedef enum {					// componentsTotal == the number of actual components
	OCT_typeEntity,		// not a component, but useful as it behaves similarly

	OCT_typeComponentTransform2D,
	OCT_typeComponentHitBox2D,

	OCT_typesTotal
} OCT_types;

typedef uint32_t OCT_ID;

typedef struct {
	OCT_ID entitySetID;
	OCT_ID entityID;
} OCT_entityHandle;

extern OCT_entityHandle _OCT_active;
extern OCT_entityHandle _OCT_errorHandle;