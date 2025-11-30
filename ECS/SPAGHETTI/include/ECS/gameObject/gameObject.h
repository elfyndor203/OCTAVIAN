#pragma once
#include "standards/ECSStandards.h"

#include "ECS/components/componentTypes/componentTypes.h"

typedef struct iOCT_gameObject iOCT_gameObject;

OCT_gameObjectID OCT_gameObject_createNew(OCT_gameObjectID parentIndex, bool is3D);
bool OCT_gameObject_hasComponent(OCT_gameObjectID iOCT_gameObject, componentTypes component);