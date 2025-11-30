#pragma once
#include "standards/ECSStandards.h"

#include "ECS/components/componentTypes/componentTypes.h"

typedef struct iOCT_gameObject OCT_gameObject;

OCT_gameObjectHandle OCT_gameObject_createNew(OCT_gameObjectHandle parentObjectHandle);

bool OCT_gameObject_hasComponent(OCT_gameObjectHandle gameObjectHandle, OCT_componentTypes component);