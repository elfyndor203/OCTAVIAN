#include "entity_internal.h"

#include "OCT_EngineStructure.h"
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#include "ECS/entityContext/entityContext_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"

size_t iOCT_entity_max = iOCT_ENTITY_DEFAULT_MAX;
OCT_handle testActiveEntity;

iOCT_entity* iOCT_entity_get(iOCT_entityContext* context, OCT_ID entityID) {
	return (iOCT_entity*)iOCT_getByID(context, entityID, OCT_ECStype_Entity);
}

/// <summary>
/// Spawns a new entity. ParentHandle may be a context or entity handle. If context, the parent of the new entity is the root of that context.
/// </summary>
/// <param name="entityContextID"></param>
/// <param name="parentID"></param>
/// <returns></returns>
OCT_handle OCT_entity_new(OCT_handle parentHandle) {
	assert(parentHandle.type == OCT_handle_entity || parentHandle.type == OCT_handle_entityContext);

	OCT_ID parentID;
	OCT_ID contextID;
	if (parentHandle.type == OCT_handle_entityContext) {	// adding to context
		parentID = iOCT_ROOT_ID;
		contextID = parentHandle.objectID;
	}
	else {	// adding as child
		parentID = parentHandle.objectID;
		contextID = parentHandle.containerID;
	}
	iOCT_entityContext* context = iOCT_entityContext_get(contextID);
	OCT_ID newEntityID = iOCT_entity_new(context, parentID);
	OCT_handle newHandle = {
		.subsystem = OCT_subsystem_ECS,
		.containerID = contextID,
		.objectID = newEntityID,
		.type = OCT_handle_entity
	};
	return newHandle;
}
OCT_ID iOCT_entity_new(iOCT_entityContext* context, OCT_ID parentID) {
	OCT_ID newID;
	iOCT_entity* newEntity;
	OCT_index newIndex;

	newEntity = (iOCT_entity*)OCT_pool_addTo(iOCT_pool_get(context, OCT_ECStype_Entity), &newIndex);
	newID = OCT_IDMap_register(&context->IDMap, newIndex);		// Register an ID first to enable other functions

	memset(newEntity, 0, sizeof(iOCT_entity)); // fill with NULL IDs

	newEntity->contextID = context->contextID;
	newEntity->entityID = newID;
	newEntity->parentID = parentID;
	newEntity->transformID = iOCT_transform2D_add(context, newID);

	iOCT_entity_updateMask(context, newID, OCT_ECStype_Entity);		// dummy marker
	return newID;
}

/// <summary>
/// Checks if a given entity has a given component. 
/// </summary>
/// <param name="entityHandle"></param>
/// <param name="component"></param>
/// <returns></returns>
bool OCT_entity_hasComponent(OCT_handle entityHandle, OCT_ECSTypes component) {
	assert(entityHandle.type == OCT_handle_entity);

	iOCT_entityContext* context = iOCT_entityContext_get(entityHandle.containerID);
	return iOCT_entity_hasComponent(context, entityHandle.objectID, component);
}
bool iOCT_entity_hasComponent(iOCT_entityContext* context, OCT_ID entityID, OCT_ECSTypes componentType) {
	if (iOCT_entity_get(context, entityID)->componentsMask & (1ULL << componentType)) { // creates a new uint_64 with a 1 at the component # bit and compares bitwise
		//printf("entity %zu DOES have componentTypes component #%d\n", entityID, component);
		return true;
	}
//	printf("entity %zu does NOT have componentTypes component #%d\n", entityID, componentType);
	return false;
}

void iOCT_entity_updateMask(iOCT_entityContext* context, OCT_ID entityID, OCT_ECSTypes componentType) {
	iOCT_entity* entity = iOCT_entity_get(context, entityID);
	entity->componentsMask |= (1ULL << componentType);
}

iOCT_entity* iOCT_entity_getParent(iOCT_entityContext* context, OCT_ID entityID) {
	return iOCT_entity_get(context, iOCT_entity_get(context, entityID)->parentID);
}

void test_entitySetActive(OCT_handle entity) {
	testActiveEntity = entity;
}








