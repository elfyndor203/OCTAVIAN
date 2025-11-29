#pragma once
#include "standards/ECSStandards.h"

#include "ECS/components/componentTypes/componentTypes.h"

typedef struct gameObject gameObject;

OCT_gameObjectID OCT_gameObject_createNew(OCT_gameObjectID parentIndex, bool is3D);
bool OCT_gameObject_hasComponent(OCT_gameObjectID gameObject, componentTypes component);