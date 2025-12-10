#pragma once
#include "standards/ECSStandards.h"

#include "ECS/entity/entity.h"
#include "ECS/components/position2D/position2D.h"
#include "ECS/components/transform2D/transform2D.h"
#include "ECS/components/hitBox2D/hitBox2D.h"

#define OCT_ROOT_OBJECT 0
#define _OCT_ENTITYSET_DEFAULT_MAX 64

typedef size_t OCT_entitySetID;

OCT_entitySetID OCT_entitySet_new();
OCT_entityHandle OCT_entitySet_root(OCT_entitySetID entitySetID);
