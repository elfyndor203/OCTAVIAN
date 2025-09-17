#pragma once
#include "ECS/gameObjects.h"
#include "ECS/components/position2D.h"
#include "ECS/components/transform2D.h"
#include "ECS/components/hitBox2D.h"

extern size_t gameObjectsCounter;
extern gameObject gameObjectsPool[MAX_GAMEOBJECTS];

extern size_t position2DCounter;
extern position2D position2DPool[MAX_GAMEOBJECTS];

extern size_t transform2DCounter;
extern transform2D transform2DPool[MAX_GAMEOBJECTS];

extern size_t hitBox2DCounter;
extern hitBox2D hitBox2DPool[MAX_GAMEOBJECTS];

