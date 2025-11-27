#pragma once
#include "standards/ECSStandards.h" 

#include "OCT_Math.h"

#define DEFAULT_ROTATION 0.0f

#define DEFAULT_SCALE_X 1.0f
#define DEFAULT_SCALE_Y 1.0f

typedef struct transform2D transform2D;

componentIndex OCT_transform2D_addNew(gameObjectIndex parentIndex);

