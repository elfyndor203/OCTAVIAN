#pragma once
#include "standards/ECSStandards.h"
#include "ECS/scene/scene.h"
#include "ECS/components/hitBox2D/hitBox2DVertices.h"

#define REN_HITBOX2D_VERTEXCOUNT 4
#define REN_HITBOX2D_INDEXCOUNT 6
#define REN_HITBOX2D_COMPONENTCOUNT 2
#define REN_TRIANGES true

vertex2D* REN_hitBox2DVertices_get(OCT_componentID engineLink);
uint32_t* REN_hitBox2DIndices_get();
