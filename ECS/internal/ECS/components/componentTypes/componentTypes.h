#pragma once
#include "standards/myStandards.h"

// top level of ECS, no ECS includes

typedef enum {					// each component type is assigned a number, and componentsTotal == the number of actual components
	componentParentObject,		// 1 to 1s
	componentPosition2D,
	componentTransform2D,
	componentHitBox2D,

	componentHitBox2DVertices, // subcomponents

	componentChildObject,		// multiple to 1s

	componentsTotal
} componentTypes;


