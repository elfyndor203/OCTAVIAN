#pragma once
#include "standards/ECSStandards.h"

#include "ECS/components/componentTypes/componentTypes.h"

typedef struct iOCT_entity OCT_entity;

OCT_entityHandle OCT_entity_new(OCT_entityHandle parentHandle);

bool OCT_entity_hasComponent(OCT_entityHandle entityHandle, OCT_componentTypes component);