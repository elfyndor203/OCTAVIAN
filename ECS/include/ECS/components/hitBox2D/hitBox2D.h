#pragma once
#include "standards/ECSStandards.h"

typedef struct hitBox2D hitBox2D;
typedef struct hitBox2DVertices hitBox2DVertices;

componentIndex OCT_hitBox2D_addNew(gameObjectIndex parentIndex);
void OCT_hitBox2D_resize(gameObjectIndex parentIndex, float sizeX, float sizeY);

