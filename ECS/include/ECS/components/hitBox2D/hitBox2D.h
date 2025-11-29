#pragma once
#include "standards/ECSStandards.h"

typedef struct hitBox2D hitBox2D;
typedef struct hitBox2DVertices hitBox2DVertices;

OCT_componentID OCT_hitBox2D_addNew(OCT_gameObjectID parentIndex);
void OCT_hitBox2D_resize(OCT_gameObjectID parentIndex, float sizeX, float sizeY);

