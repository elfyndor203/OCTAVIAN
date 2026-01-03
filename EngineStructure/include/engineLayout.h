#pragma once

typedef enum {
	_OCT_ECS = 1000,
	_OCT_Renderer = 2000
} _OCT_subsystemList;

typedef enum {					// componentsTotal == the number of actual components
	OCT_componentEntity,		// not a component, but useful as it behaves similarly

	OCT_componentPosition2D,	// 1 to 1s
	OCT_componentTransform2D,
	OCT_componentHitBox2D,

	OCT_componentsTotal
} OCT_componentTypes;
typedef size_t OCT_componentID;

typedef struct {
	size_t entitySetID;
	size_t entityID;
} OCT_entityHandle;

extern OCT_entityHandle _OCT_active;
extern OCT_entityHandle _OCT_errorHandle;