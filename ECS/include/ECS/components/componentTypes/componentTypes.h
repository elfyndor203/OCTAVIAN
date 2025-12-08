#pragma once

typedef enum {					// componentsTotal == the number of actual components
	componentParentObject,		// 1 to 1s
	componentPosition2D,
	componentTransform2D,
	componentHitBox2D,

	componentSprite2D,

	componentChildObject,		// multiple to 1s

	componentsTotal
} OCT_componentTypes;
