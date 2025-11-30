#pragma once
#include "standards/ECSStandards.h"

#include "OCT_Math.h"

#define DEFAULT_POSITION_X 0
#define DEFAULT_POSITION_Y 0

typedef struct iOCT_position2D OCT_position2D;

OCT_componentID OCT_transform2D_addNew(OCT_sceneID sceneID, OCT_gameObjectID parentID);