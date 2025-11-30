#pragma once
#include "ECS_Renderer_Output/hitBoxData.h"
#include "standards/ECSStandards_internal.h"

#include <string.h>

#include "ECS/components/hitBox2D/hitBox2DVertices_internal.h"

typedef struct hitBox2DOutputVertexArray {
	vertex2D bottomLeft;
	vertex2D bottomRight;
	vertex2D topRight;
	vertex2D topLeft;
} hitBox2DOutputVertexArray;

