#pragma once
#include "standards/ECSStandards.h"

OCT_entityHandle OCT_entity_new(OCT_entityHandle parentHandle);
bool OCT_entity_hasComponent(OCT_entityHandle entityHandle, OCT_types component);
void test_entitySetActive(OCT_entityHandle entity);