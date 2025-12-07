#pragma once
#include "standards/ECSStandards.h"
#include "ECS/components/componentTypes/componentTypes.h"

#include "ECS/entity/entity.h"
#include "ECS/components/position2D/position2D.h"
#include "ECS/components/transform2D/transform2D.h"
#include "ECS/components/hitBox2D/hitBox2D.h"

#define OCT_ROOT_OBJECT 0

typedef struct iOCT_entitySet OCT_entitySet;
typedef size_t OCT_entitySetID;

//OCT_entitySet* OCT_entitySet_get(OCT_entitySetID entitySetID);
OCT_entitySetID OCT_entitySet_new();
OCT_entityHandle OCT_entitySet_getRootHandle(OCT_entitySetID entitySetID);
