#pragma once
#include "ECS/types.h"

#include "OCT_engineStructure.h"
#include <stdbool.h>

OCT_handle OCT_entity_new(OCT_handle parentHandle);
bool OCT_entity_hasComponent(OCT_handle entityHandle, OCT_ECSTypes component);
void test_entitySetActive(OCT_handle entity);