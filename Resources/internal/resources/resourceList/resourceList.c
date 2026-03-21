#include "resources/resourceList/resourceList_internal.h"
#include "resources/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"

#include "resources/resource/resource_internal.h"
#include "module/RESModule_internal.h"

iOCT_resourceList* iOCT_resourceList_get(iOCT_resourceType type) {
	iOCT_resourceList* list;
	switch (type) {
	case iOCT_resourceImage:
		list = &iOCT_RESModule_instance.imageList;
		break;
	case iOCT_resourceAudio:
		list = &iOCT_RESModule_instance.audioList;
		break;
	default:
		list = NULL;
	}
	return list;
}

iOCT_resourceList iOCT_resourceList_open(iOCT_resourceType type) {
	iOCT_resourceList newList;
	OCT_ID newID = type;

	newList.listID = newID;
	newList.map = cOCT_IDMap_init(newID, iOCT_POOLSIZE_DEFAULT);
	newList.pool = cOCT_pool_init(newID, iOCT_POOLSIZE_DEFAULT, sizeof(iOCT_resource));
	newList.type = type;

	return newList;
}

void iOCT_resourceList_close(iOCT_resourceList* list) {
	cOCT_IDMap_free(&list->map);
	cOCT_pool_free(&list->pool);
}