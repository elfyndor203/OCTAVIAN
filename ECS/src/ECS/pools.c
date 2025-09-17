#include "ECS/pools.h"

size_t gameObjectsCounter = 0;
gameObject gameObjectsPool[MAX_GAMEOBJECTS] = { 0 };

size_t position2DCounter = 0;
position2D position2DPool[MAX_GAMEOBJECTS] = { 0 };

size_t transform2DCounter = 0;
transform2D transform2DPool[MAX_GAMEOBJECTS] = { 0 };

size_t hitBox2DCounter = 0;
hitBox2D hitBox2DPool[MAX_GAMEOBJECTS] = { 0 };