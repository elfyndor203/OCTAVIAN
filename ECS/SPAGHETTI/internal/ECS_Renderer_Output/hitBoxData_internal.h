#pragma once
#include "ECS_Renderer_Output/hitBoxData.h"
#include "standards/ECSStandards_internal.h"

#include <string.h>

#include "ECS/components/hitBox2D/hitBox2DVertices_internal.h"

typedef struct hitBox2DOutputVertexArray {
	OCT_vertex2D bottomLeft;
	OCT_vertex2D bottomRight;
	OCT_vertex2D topRight;
	OCT_vertex2D topLeft;
} hitBox2DOutputVertexArray;

