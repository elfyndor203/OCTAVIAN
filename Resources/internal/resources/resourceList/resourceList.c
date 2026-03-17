#include "resources/resourceList/resourceList_internal.h"
#include "resources/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"

#include "resources/resource/resource_internal.h"
#include "resources/module/RESModule_internal.h"

iOCT_resourceList* iOCT_resourceList_get(OCT_ID listID) {
	OCT_index index = iOCT_IDMap_getIndex(&iOCT_RESModule_instance.IDMap, listID);
	return (iOCT_resourceList*)iOCT_pool_access(&iOCT_RESModule_instance.pool, index);
}

OCT_ID iOCT_resourceList_open(iOCT_resourceType type) {
	OCT_index newIndex;
	OCT_ID newID;
	iOCT_resourceList* newList; 
	
	newList = (iOCT_resourceList*)iOCT_pool_addEntry(&iOCT_RESModule_instance.pool, &newIndex);
	newID = iOCT_IDMap_register(&iOCT_RESModule_instance.IDMap, newIndex);

	newList->listID = newID;
	newList->map = iOCT_IDMap_init(newID, OCT_POOLSIZE_DEFAULT);
	newList->pool = iOCT_pool_init(newID, OCT_POOLSIZE_DEFAULT, sizeof(iOCT_resource));
	newList->type = type;

	return newID;
}

void iOCT_resourceList_close(iOCT_resourceList* list) {
	iOCT_IDMap_free(&list->map);
	iOCT_pool_free(&list->pool);

	OCT_index index = iOCT_IDMap_deregister(&iOCT_RESModule_instance.IDMap, list->listID);
	iOCT_pool_deleteEntry(&iOCT_RESModule_instance.pool, index, true);
}