#pragma once
#include <stdint.h>

typedef enum {					// componentsTotal == the number of actual components
	componentParentObject,		// 1 to 1s
	componentPosition2D,
	componentTransform2D,
	componentHitBox2D,

	componentHitBox2DVertices, // subcomponents

	componentChildObject,		// multiple to 1s

	componentsTotal
} OCT_componentTypes;
