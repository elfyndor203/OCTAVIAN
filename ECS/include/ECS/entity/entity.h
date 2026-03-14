#pragma once
#include "OCT_EngineStructure.h"

OCT_engineHandle OCT_entity_new(OCT_engineHandle parentHandle);
bool OCT_entity_hasComponent(OCT_engineHandle entityHandle, OCT_types component);
void test_entitySetActive(OCT_engineHandle entity);