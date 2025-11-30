#pragma once
#include "ECS/components/hitBox2D/hitBox2DVertices.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"
#include "OCT_Math.h"

typedef struct hitBox2DVertices {
	OCT_componentID poolIndex;
	OCT_componentID hitBoxIndex;

	vertex2D localOrigin;
	vertex2D bottomLeft;
	vertex2D bottomRight;
	vertex2D topRight;
	vertex2D topLeft;
} hitBox2DVertices;

OCT_componentID hitBox2D_generateVertices(OCT_gameObjectID parentIndex);