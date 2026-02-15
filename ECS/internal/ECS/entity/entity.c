#include "entity_internal.h"
#include <string.h>

#include "ECS/entityContext/entityContext_internal.h"
#include "ECS/components/position2D/position2D_internal.h"		// two required components
#include "ECS/components/transform2D/transform2D_internal.h"

size_t iOCT_entity_max = iOCT_ENTITY_DEFAULT_MAX;
OCT_entityHandle testActiveEntity;

// Registers a new entity with the IDMap, then fills in required components
OCT_ID iOCT_entity_new(OCT_ID entityContextID, OCT_ID parentID) {
	OCT_ID newID;
	iOCT_entity* newEntity;
	
	newID = iOCT_IDMap_registerID(entityContextID, OCT_typeEntity);		// Register an ID first to enable other functions
	newEntity = iOCT_getByID(entityContextID, OCT_typeEntity, newID);	// Get the empty pool slot
	memset(newEntity, 0, sizeof(iOCT_entity));							// Make sure the slot is empty

	newEntity->entityContextID = entityContextID;
	newEntity->entityID = newID;
	newEntity->parentID = parentID;
	newEntity->transformID = iOCT_transform2D_new(entityContextID, newID);
	newEntity->hitBoxID = iOCT_NO_COMPONENT;
	
	if (parentID != iOCT_NOPARENT) {
		iOCT_entity_updateMask(entityContextID, parentID, OCT_typeEntity);	// Notify parent that it now has a child
	}

	printf("\nCreated new entity #%zu in entityContext #%zu as a child of entity %zu \n", newID, entityContextID, parentID);
	return newID;
}

void iOCT_entity_updateMask(OCT_ID entityContextID, OCT_ID entityID, OCT_types componentType) {
	iOCT_entity* entity = iOCT_getByID(entityContextID, componentType, entityID);
	entity->componentsMask |= (1ULL << componentType);
}

bool iOCT_entity_hasComponent(iOCT_entityContextID entitySetID, iOCT_entityID entityID, OCT_types component) {
	if (iOCT_entity_get(entitySetID, entityID)->componentsMask & (1ULL << component)) {// creates a new uint_64 with a 1 at the component # bit and compares bitwise
		//printf("entity %zu DOES have componentTypes component #%d\n", entityID, component);
		return true;
	}
	printf("entity %zu does NOT have componentTypes component #%d\n", entityID, component);
	return false;
}

/// API








