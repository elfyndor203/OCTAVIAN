#include "entity_internal.h"

#include "ECS/entitySet/entitySet_internal.h"
#include "ECS/components/position2D/position2D_internal.h"		// two required components
#include "ECS/components/transform2D/transform2D_internal.h"

size_t iOCT_entity_max = iOCT_ENTITY_DEFAULT_MAX;

////////////////////////////////////////////////////////// getter functions
iOCT_entity* iOCT_entity_get(iOCT_entitySetID entitySetID, iOCT_entityID entityID) {
	// check if entitySet exists, then if object exists within that entitySet
	if (iOCT_entitySet_get(entitySetID) == iOCT_GET_FAILED || entityID > iOCT_entitySet_get(entitySetID)->entityCounter) {	
		OCT_logError(ERR_ENTITY_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	//printf("Got entity #%zu from entitySet #%zu\n", entityID, entitySetID);
	return &iOCT_entitySet_get(entitySetID)->entityPool[entityID];	// access the entitySet, access the entity, and return its pointer
}

iOCT_entity* iOCT_entity_getPool(iOCT_entitySetID entitySetID) {
	if (iOCT_entitySet_get(entitySetID) == iOCT_GET_FAILED) {
		OCT_logError(ERR_ENTITYPOOL_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	//printf("Got entityPool from entitySet #%zu\n", entitySetID);
	return &iOCT_entitySet_get(entitySetID)->entityPool;
}

OCT_counter* iOCT_entity_getCounter(iOCT_entitySetID entitySetID) {
	if (iOCT_entitySet_get(entitySetID) == iOCT_GET_FAILED) {
		OCT_logError(ERR_ENTITYCOUNTER_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	//printf("Got entityCounter from entitySet #%zu\n", entitySetID);
	return &iOCT_entitySet_get(entitySetID)->entityCounter;
}
////////////////////////////////////////////////////////// getter functions

iOCT_entityID iOCT_entity_createNew(iOCT_entitySetID entitySetID, iOCT_entityID parentID) {
	if (*iOCT_entity_getCounter(entitySetID) >= (iOCT_entity_max-1)) {
		logError(ERR_ENTITYPOOL_FULL);
		return iOCT_GAMEOBJECT_FAILED;
	}
	iOCT_entity newEntity = { 0 };

	iOCT_entity* parent = iOCT_entity_get(entitySetID, parentID);	// store pointer to its parent
	parent->componentsMask |= (1ULL << componentChildObject);				// parent object knows it exists

	iOCT_entityID entityID = *iOCT_entity_getCounter(entitySetID);	// setting default values
	newEntity.entitySetID = entitySetID;
	newEntity.entityID = entityID;								// it can find itself			
	newEntity.parentID = parentID;								// it can find its parent
	newEntity.positionID = iOCT_NO_COMPONENT;
	newEntity.transformID = iOCT_NO_COMPONENT;
	newEntity.hitBoxID = iOCT_NO_COMPONENT;							// 	

	iOCT_entity_getPool(entitySetID)[*iOCT_entity_getCounter(entitySetID)] = newEntity;	// store function before adding requirements
	*iOCT_entity_getCounter(entitySetID) += 1;

	iOCT_position2D_addNew(entitySetID, entityID);							// add requirements to the stored object
	transform2D_addNew(entitySetID, entityID);

	printf("\nCreated new entity #%zu in entitySet #%zu as a child of object %zu \n", entityID, entitySetID, parentID);
	return entityID;
}

bool iOCT_entity_hasComponent(iOCT_entitySetID entitySetID, iOCT_entityID entityID, OCT_componentTypes component) {
	if (iOCT_entity_get(entitySetID, entityID)->componentsMask & (1ULL << component)) {// creates a new uint_64 with a 1 at the component # bit and compares bitwise
		//printf("entity %zu DOES have componentTypes component #%d\n", entityID, component);
		return true;
	}
	printf("entity %zu does NOT have componentTypes component #%d\n", entityID, component);
	return false;
}

/// API








