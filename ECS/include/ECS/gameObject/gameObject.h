#pragma once
#include "standards/ECSStandards.h"

#include "ECS/components/componentTypes/componentTypes.h"

typedef struct gameObject gameObject;

gameObjectIndex OCT_gameObject_createNew(gameObjectIndex parentIndex, bool is3D);
bool OCT_gameObject_hasComponent(gameObjectIndex gameObject, componentTypes component);