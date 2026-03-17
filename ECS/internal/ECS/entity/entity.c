#include "entity_internal.h"
#include <string.h>
#include <inttypes.h>
#include <stdio.h>

#include "ECS/entityContext/entityContext_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"

size_t iOCT_entity_max = iOCT_ENTITY_DEFAULT_MAX;
OCT_handle testActiveEntity;

iOCT_entity* iOCT_entity_get(iOCT_entityContext* context, OCT_ID entityID) {
	return (iOCT_entity*)iOCT_getByID(context, entityID, OCT_typeEntity);
}

/// <summary>
/// Spawns a new entity. ParentHandle may be a context or entity handle. If context, the parent of the new entity is the root of that context.
/// </summary>
/// <param name="entityContextID"></param>
/// <param name="parentID"></param>
/// <returns></returns>
OCT_handle OCT_entity_new(OCT_handle parentHandle) {
	OCT_ID parentID;
	OCT_ID contextID;
	if (parentHandle.ownerID == OCT_subsystem_ECS) {	// adding to context
		parentID = iOCT_ROOT_ID;
		contextID = parentHandle.objectID;
	}
	else {	// adding as child
		parentID = parentHandle.objectID;
		contextID = parentHandle.ownerID;
	}
	iOCT_entityContext* context = iOCT_entityContext_get(contextID);
	OCT_ID newEntityID = iOCT_entity_new(context, parentID);
	OCT_handle newHandle = { contextID, newEntityID };
	return newHandle;
}
OCT_ID iOCT_entity_new(iOCT_entityContext* context, OCT_ID parentID) {
	OCT_ID newID;
	iOCT_entity* newEntity;
	OCT_index newIndex;

	newEntity = OCT_pool_addTo(iOCT_pool_get(context, OCT_typeEntity), &newIndex);
	newID = OCT_IDMap_register(&context->IDMap, OCT_typeEntity, newIndex);		// Register an ID first to enable other functions

	memset(newEntity, 0, sizeof(iOCT_entity)); // fill with NULL IDs

	newEntity->contextID = context->contextID;
	newEntity->entityID = newID;
	newEntity->parentID = parentID;
	newEntity->transformID = iOCT_transform2D_add(context, newID);

	iOCT_entity_updateMask(context, newID, OCT_typeEntity);		// dummy marker
	return newID;
}

/// <summary>
/// Checks if a given entity has a given component. 
/// </summary>
/// <param name="entityHandle"></param>
/// <param name="component"></param>
/// <returns></returns>
bool OCT_entity_hasComponent(OCT_handle entityHandle, OCT_ECStypes component) {
	iOCT_entityContext* context = iOCT_entityContext_get(entityHandle.ownerID);
	return iOCT_entity_hasComponent(context, entityHandle.objectID, component);
}
bool iOCT_entity_hasComponent(iOCT_entityContext* context, OCT_ID entityID, OCT_ECStypes componentType) {
	if (iOCT_entity_get(context, entityID)->componentsMask & (1ULL << componentType)) { // creates a new uint_64 with a 1 at the component # bit and compares bitwise
		//printf("entity %zu DOES have componentTypes component #%d\n", entityID, component);
		return true;
	}
//	printf("entity %zu does NOT have componentTypes component #%d\n", entityID, componentType);
	return false;
}

void iOCT_entity_updateMask(iOCT_entityContext* context, OCT_ID entityID, OCT_ECStypes componentType) {
	iOCT_entity* entity = iOCT_entity_get(context, entityID);
	entity->componentsMask |= (1ULL << componentType);
}

iOCT_entity* iOCT_entity_getParent(iOCT_entityContext* context, OCT_ID entityID) {
	return iOCT_entity_get(context, iOCT_entity_get(context, entityID)->parentID);
}

void test_entitySetActive(OCT_handle entity) {
	testActiveEntity = entity;
}








