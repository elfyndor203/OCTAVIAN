#pragma once
#include "standards/ECSStandards.h"
#include "ECS/entitySet/entitySet.h"

#define REN_HITBOX2D_VERTEXCOUNT 4
#define REN_HITBOX2D_INDEXCOUNT 6
#define REN_HITBOX2D_COMPONENTCOUNT 2
#define REN_TRIANGES false

typedef struct hitBox2DOutputVertexArray hitBox2DOutputVertexArray;

size_t* REN_hitBox2DVertices_getCount();
size_t* REN_hitBox2DIndices_getCount();

float* REN_hitBox2DVertices_get(OCT_entityHandle entityHandle);
unsigned int* REN_hitBox2DIndices_get();
