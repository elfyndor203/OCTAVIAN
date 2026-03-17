#pragma once
#include "ECS/types.h"

OCT_handle OCT_entity_new(OCT_handle parentHandle);
bool OCT_entity_hasComponent(OCT_handle entityHandle, OCT_ECStypes component);
void test_entitySetActive(OCT_handle entity);