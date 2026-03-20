#include "RESModule_internal.h"
#include "resources/types_internal.h"

#include "cOCT_EngineStructure.h"

#include "resources/resourceList/resourceList_internal.h"
#include "resources/resource/resource_internal.h"

cOCT_module iOCT_RESModule_instance = { 0 };
OCT_ID iOCT_resourceList_IDList[iOCT_resourceTypes_total];

void iOCT_RESModule_init() {
	iOCT_module_init(&iOCT_RESModule_instance, iOCT_resourceTypes_total, sizeof(iOCT_resourceList));
	for (int type = 0; type < iOCT_resourceTypes_total; type++) {
		iOCT_resourceList_IDList[type] = iOCT_resourceList_open(type);
	}
}

void iOCT_RESModule_free() {
	iOCT_resourceList* array = (iOCT_resourceList*)iOCT_RESModule_instance.pool.array;

	for (int index = 0; index < iOCT_RESModule_instance.pool.count; index++) {
		iOCT_resourceList* list = &array[index];
		iOCT_resourceList_close(list);
	}
}