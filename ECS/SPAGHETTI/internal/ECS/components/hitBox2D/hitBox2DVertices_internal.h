#pragma once
#include "ECS/components/hitBox2D/hitBox2DVertices.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"
#include "OCT_Math.h"

typedef struct hitBox2DOutput {
	OCT_vertex2D bottomLeft;
	OCT_vertex2D bottomRight;
	OCT_vertex2D topRight;
	OCT_vertex2D topLeft;
} hitBox2DOutput;

typedef struct hitBox2DVertices {
	OCT_componentID poolIndex;
	OCT_componentID hitBoxIndex;

	OCT_vertex2D localOrigin;
	hitBox2DOutput corners;
} hitBox2DVertices;

OCT_componentID hitBox2D_generateVertices(OCT_gameObjectID parentIndex);