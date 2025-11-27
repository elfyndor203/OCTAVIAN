#pragma once
#include "standards/ECSStandards.h"

#include "OCT_Math.h"

#define DEFAULT_POSITION_X 0
#define DEFAULT_POSITION_Y 0

typedef struct position2D position2D;

componentIndex OCT_position2D_addNew(gameObjectIndex parentIndex);
