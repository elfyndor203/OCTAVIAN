#pragma once
#include "myStandards.h"

// top level of ECS, no ECS includes

typedef enum {				// each component type is assigned a number, and componentsTotal == the number of actual components
	componentParentObject,
	componentPosition2D,
	componentTransform2D,
	componentHitBox2D,
	componentChildObject,

	componentsTotal
} componentTypes;



