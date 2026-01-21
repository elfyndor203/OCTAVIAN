#include "position2D_internal.h"

#include "ECS/entity/entity_internal.h"
#include "ECS/entitySet/entitySet_internal.h"

size_t iOCT_MAX_POSITION2D = iOCT_ENTITY_DEFAULT_MAX;

OCT_vector2D defaultPosition2D = { DEFAULT_POSITION_X, DEFAULT_POSITION_Y };

iOCT_position2D* iOCT_position2D_get(iOCT_entityContextID entitySetID, iOCT_entityID parentID) {
	iOCT_entityContext* entitySet = iOCT_entitySet_get(entitySetID);
	if (entitySet == iOCT_GET_FAILED || parentID >= entitySet->entityCounter) {
		OCT_logError(ERR_POSITION2D_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	iOCT_entity* parent = iOCT_entity_get(entitySetID, parentID);
	if (parent == iOCT_GET_FAILED) {
		OCT_logError(ERR_POSITION2D_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	if (parent->positionID == iOCT_NO_COMPONENT) {
		OCT_logError(ERR_POSITION2D_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	//printf("Got position2D from entity #%zu from entitySet #%zu\n", parentID, entitySetID);
	return &entitySet->position2DPool[parent->positionID];
}

iOCT_position2D* iOCT_position2D_getPool(iOCT_entityContextID entitySetID) {
	iOCT_entityContext* entitySet = iOCT_entitySet_get(entitySetID);
	if (entitySet == iOCT_GET_FAILED) {
		OCT_logError(ERR_POSITION2DPOOL_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	//printf("Got position2D pool from entitySet #%zu\n", entitySetID);
	return entitySet->position2DPool; // array decay to pointer
}
OCT_counter* iOCT_position2D_getCounter(iOCT_entityContextID entitySetID) {
	iOCT_entityContext* entitySet = iOCT_entitySet_get(entitySetID);
	if (entitySet == iOCT_GET_FAILED) {
		OCT_logError(ERR_POSITION2DCOUNTER_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}

	//printf("Got position2D counter from entitySet #%zu\n", entitySetID);
	return &entitySet->position2DCounter;
}

iOCT_componentID iOCT_position2D_addNew(iOCT_entityContextID entitySetID, iOCT_entityID parentID) {								// attaches a new default position2D to some entity
	if (iOCT_entity_hasComponent(entitySetID, parentID, OCT_componentPosition2D)) {
		OCT_logError(WARNING_COMPONENT_REPLACED);
	}
	OCT_counter* counter = iOCT_position2D_getCounter(entitySetID);
	if (*counter >= iOCT_MAX_POSITION2D) {
		logError(ERR_POSITION2DPOOL_FULL);
		return iOCT_POSITION2D_FAILED;
	}

	iOCT_position2D newPosition2D = { 0 };

	iOCT_entity* parent = iOCT_entity_get(entitySetID, parentID);
	parent->componentsMask |= (1ULL << OCTcomponentPosition2D);		// parent object knows it exists

	iOCT_componentID positionID = *counter;		// setting values
	newPosition2D.positionID = positionID;									// it can find itself
	newPosition2D.parentID = parentID;										// it can find its parent object
	parent->positionID = newPosition2D.positionID;					// parent object can find it
	newPosition2D.globalPosition2D = defaultPosition2D;						// default values
	newPosition2D.localPosition2D = defaultPosition2D;

	iOCT_position2D_getPool(entitySetID)[*counter] = newPosition2D;			// add it to the pool
	*counter += 1;

	printf("Added new position2D to object #%zu in entitySet #%zu\n", parentID, entitySetID);
	return positionID;
}

iOCT_componentID iOCT_position2D_new(iOCT_entityContext* entityCtx, iOCT_entity* parent) {
	if (iOCT_entity_hasComponent(entityCtx, parent, OCT_componentPosition2D)) {
		OCT_logError(WARNING_COMPONENT_REPLACED);
	}
	if (iOCT_pool_full(entityCtx, OCT_componentPosition2D)) {
		// expand
	}

	parent->componentsMask |= (1ULL << OCT_componentPosition2D);

	iOCT_position2D newPosition2D = { 0 };
	newPosition2D.positionID = iOCT_ID_new(entityCtx, )

}


void iOCT_position2D_move(iOCT_entityContextID entitySetID, iOCT_entityID parentID, OCT_vector2D distance) {
	iOCT_position2D* position = iOCT_position2D_get(entitySetID, parentID);
	position->globalPosition2D.x += distance.x;
	position->globalPosition2D.y += distance.y;
	position->localPosition2D.x += distance.x;
	position->localPosition2D.y += distance.y;
}
