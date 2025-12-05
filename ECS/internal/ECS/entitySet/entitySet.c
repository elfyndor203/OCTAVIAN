#include "entitySet_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"

size_t iOCT_entitySet_max = iOCT_ENTITYSET_DEFAULT_MAX;

OCT_counter iOCT_entitySetCounter = 0;

iOCT_entitySet* iOCT_entitySet_get(iOCT_entitySetID entitySetID) {
	if (entitySetID > iOCT_entitySet_max || iOCT_entitySetPool[entitySetID] == 0) {
		OCT_logError(ERR_ENTITYSET_DOES_NOT_EXIST);
		return iOCT_GET_FAILED;
	}
	printf("Got entitySet #%zu\n", entitySetID);
	return iOCT_entitySetPool[entitySetID];
}

iOCT_entitySetID iOCT_entitySet_new() {
	iOCT_entitySet* newEntitySet = calloc(1, sizeof(iOCT_entitySet));
	if (!newEntitySet) {
		OCT_logError(EXIT_ENTITYSET_FAILED);				//NOTE: 2 EXITS
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
		return 0;
	}

		// root object creation
	newEntitySet->entitySetID = iOCT_entitySetCounter;
	iOCT_entity blankRootObject = { 0 };
	blankRootObject.hitBoxID = iOCT_NO_COMPONENT;		// NOTE_NEW_COMPONENTS
	blankRootObject.componentsMask |= (1ULL << componentParentObject);
	blankRootObject.componentsMask |= (1ULL << componentPosition2D);
	blankRootObject.componentsMask |= (1ULL << componentTransform2D);
	newEntitySet->rootObject = blankRootObject;

	iOCT_entitySetPool[iOCT_entitySetCounter] = newEntitySet;		// store entitySet

	iOCT_entity_getPool(newEntitySet->entitySetID)[0] = blankRootObject;	// store root object in entitySet
	*iOCT_entity_getCounter(newEntitySet->entitySetID) += 1;

	iOCT_entitySetID entitySetID = iOCT_entitySetCounter;	//
	newEntitySet->entitySetID = iOCT_entitySetCounter;		// log own index
	iOCT_entitySetCounter += 1;						// update counter
	
	printf("Created entitySet with entitySetID %zu\n", entitySetID);
	return entitySetID;
}

void iOCT_entitySet_initialize() {
	memset(iOCT_entitySetPool, 0, sizeof(iOCT_entitySetPool));
	printf("EntitySet pool zeroed out\n");
}



