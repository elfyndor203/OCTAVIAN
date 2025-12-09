#pragma once

typedef enum {
	_OCT_ECS,
	_OCT_Renderer
} _OCT_subsystemList;

typedef enum {					// componentsTotal == the number of actual components
	componentParentObject,		// 1 to 1s
	componentPosition2D,
	componentTransform2D,
	componentHitBox2D,

	componentSprite2D,

	componentChildObject,		// multiple to 1s

	componentsTotal
} OCT_componentTypes;

typedef struct {
	size_t entitySetID;
	size_t entityID;
} OCT_entityHandle;

extern OCT_entityHandle _OCT_ACTIVE;
