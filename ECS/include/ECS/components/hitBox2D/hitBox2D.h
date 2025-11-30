#pragma once
#include "standards/ECSStandards.h"

#define HITBOX_VERTEX_DATATYPE float

typedef struct hitBox2D hitBox2D;

OCT_componentID OCT_hitBox2D_addNew(OCT_gameObjectID parentIndex);
void OCT_hitBox2D_resize(OCT_gameObjectID parentIndex, float sizeX, float sizeY);

