#pragma once
#include "standards/ECSStandards.h" 

#include "OCT_Math.h"

#define DEFAULT_ROTATION 0.0f

#define DEFAULT_SCALE_X 1.0f
#define DEFAULT_SCALE_Y 1.0f

typedef struct iOCT_transform2D iOCT_transform2D;

OCT_componentID OCT_transform2D_addNew(OCT_gameObjectID parentIndex);

