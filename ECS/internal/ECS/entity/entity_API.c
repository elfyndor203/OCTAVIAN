#include "ECS/entity/entity.h"
#include "entity_internal.h"

OCT_entityHandle OCT_entity_new(OCT_entityHandle parentHandle) {
	iOCT_entitySetID entitySetID = parentHandle.entitySetID;
	iOCT_entityID parentID = parentHandle.entityID;
	iOCT_entityID newEntityID =  iOCT_entity_createNew(entitySetID, parentID);
	OCT_entityHandle newHandle = { entitySetID, newEntityID };
	return newHandle;
}

bool OCT_entity_hasComponent(OCT_entityHandle entityHandle, OCT_componentTypes component) {
	iOCT_entitySetID entitySetID = entityHandle.entitySetID;
	iOCT_entityID entityID = entityHandle.entityID;
	return iOCT_entity_hasComponent(entitySetID, entityID, component);
}

void test_entitySetActive(OCT_entityHandle entity) {
	testActiveEntity = entity;
}
