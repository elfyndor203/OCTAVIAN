#pragma once

#define INITIAL_MAX_COMPONENTS_PER_TYPE 256
#define ADD_TO_POOL (poolType, poolName, poolCounterName)

#include "ECS/components/position2D.h"
#include "ECS/components/transform2D.h"
#include "ECS/components/hitBox2D.h"

position2D position2DPool[INITIAL_MAX_COMPONENTS_PER_TYPE];
size_t position2DCounter;
size_t addNewPosition2D(size_t parentIndex);

transform2D transform2DPool[INITIAL_MAX_COMPONENTS_PER_TYPE];
size_t transform2DCounter;
size_t addNewTransform2D(size_t parentIndex);

hitBox2D hitBox2DPool[INITIAL_MAX_COMPONENTS_PER_TYPE];
size_t hitBox2DCounter;
size_t addNewHitBox2D(size_t parentIndex);

void initializeAllPools();

