#include "entity_internal.h"
#include <string.h>
#include <inttypes.h>
#include <stdio.h>

#include "ECS/entityContext/entityContext_internal.h"
#include "ECS/entityContext/IDMap_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"

size_t iOCT_entity_max = iOCT_ENTITY_DEFAULT_MAX;
OCT_entityHandle testActiveEntity;

iOCT_entity* iOCT_entity_get(OCT_ID entityContextID, OCT_ID entityID) {
	return (iOCT_entity*)iOCT_getByID(entityContextID, entityID, OCT_typeEntity);
}

/// <summary>
/// Registers a new entity in the given entityContext. Fills in required components: transform
/// </summary>
/// <param name="entityContextID"></param>
/// <param name="parentID"></param>
/// <returns></returns>
OCT_entityHandle OCT_entity_new(OCT_entityHandle parentHandle) {
	OCT_ID entityContextID = parentHandle.entityContextID;
	OCT_ID parentID = parentHandle.entityID;
	OCT_ID newEntityID = iOCT_entity_new(entityContextID, parentID);
	OCT_entityHandle newHandle = { entityContextID, newEntityID };
	return newHandle;
}
OCT_ID iOCT_entity_new(OCT_ID entityContextID, OCT_ID parentID) {

	OCT_ID newID;
	iOCT_entity* newEntity;
	
	newID = iOCT_IDMap_register(entityContextID, OCT_typeEntity);		// Register an ID first to enable other functions
	if (parentID == iOCT_NOPARENT) {
	//	printf("\nNEW entity %10" PRIu64 " in entityContext % " PRIu64 " as ROOT\n", newID, entityContextID);
	}
	else {
	//	printf("\nNEW entity %10" PRIu64 " in entityContext %" PRIu64 " as a child of entity % " PRIu64 "\n", newID, entityContextID, parentID);
	}
	newEntity = iOCT_getByID(entityContextID, newID, OCT_typeEntity);	// Get the empty pool slot
	memset(newEntity, 0, sizeof(iOCT_entity));							// Make sure the slot is empty

	newEntity->entityContextID = entityContextID;
	newEntity->entityID = newID;
	newEntity->parentID = parentID;
	newEntity->transformID = iOCT_transform2D_add(entityContextID, newID);
	newEntity->hitBoxID = iOCT_NO_COMPONENT;
	iOCT_entity_updateMask(entityContextID, newID, OCT_typeEntity);		// dummy marker

	return newID;
}

/// <summary>
/// Checks if a given entity has a given component. 
/// </summary>
/// <param name="entityHandle"></param>
/// <param name="component"></param>
/// <returns></returns>
bool OCT_entity_hasComponent(OCT_entityHandle entityHandle, OCT_types component) {
	OCT_ID entityContextID = entityHandle.entityContextID;
	OCT_ID entityID = entityHandle.entityID;
	return iOCT_entity_hasComponent(entityContextID, entityID, component);
}
bool iOCT_entity_hasComponent(OCT_ID entityContextID, OCT_ID entityID, OCT_types componentType) {
	if (iOCT_entity_get(entityContextID, entityID)->componentsMask & (1ULL << componentType)) { // creates a new uint_64 with a 1 at the component # bit and compares bitwise
		//printf("entity %zu DOES have componentTypes component #%d\n", entityID, component);
		return true;
	}
//	printf("entity %zu does NOT have componentTypes component #%d\n", entityID, componentType);
	return false;
}

void iOCT_entity_updateMask(OCT_ID entityContextID, OCT_ID entityID, OCT_types componentType) {
	iOCT_entity* entity = iOCT_entity_get(entityContextID, entityID);
	entity->componentsMask |= (1ULL << componentType);
}

iOCT_entity* iOCT_entity_getParent(OCT_ID contextID, OCT_ID entityID) {
	return iOCT_entity_get(contextID, iOCT_entity_get(contextID, entityID)->parentID);
}

void test_entitySetActive(OCT_entityHandle entity) {
	testActiveEntity = entity;
}








