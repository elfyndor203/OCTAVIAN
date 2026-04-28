#include "ECSModule_internal.h"
#include "ECS/entityContext/entityContext_internal.h"

#include "cOCT_EngineStructure.h"
#include <stdlib.h>
#include <stdio.h>

#include "_ECS_Output/_ECS_include.h"

iOCT_ECSModule iOCT_ECSModule_instance = { 0 };

void OCT_ECSModule_init() {
	iOCT_ECSModule_init();
}
void iOCT_ECSModule_init() {
	iOCT_ECSModule_instance.contextMap = cOCT_IDMap_init(OCT_subsystem_ECS, cOCT_POOLSIZE_DEFAULT);
	iOCT_ECSModule_instance.contextPool = cOCT_pool_init(OCT_subsystem_ECS, cOCT_POOLSIZE_DEFAULT, sizeof(iOCT_entityContext));

	iOCT_ECSModule_instance.physicsDataPool = cOCT_pool_init(OCT_subsystem_ECS, cOCT_POOLSIZE_DEFAULT, sizeof(_OCT_snapshot_physics));
	iOCT_ECSModule_instance.activeCamera.type = OCT_handle_NULL;
}

void OCT_ECSModule_free() {
	iOCT_entityContext* array = (iOCT_entityContext*)iOCT_ECSModule_instance.contextPool.array;

	iOCT_entityContext* context;
	for (int index = 0; index < iOCT_ECSModule_instance.contextPool.count; index++) {
		context = &array[index];
		iOCT_entityContext_close(context);
	}
	cOCT_IDMap_free(&iOCT_ECSModule_instance.contextMap);
	cOCT_pool_free(&iOCT_ECSModule_instance.contextPool);
}

void OCT_ECSModule_update() {
	// do order checks here
	iOCT_ECSModule_update();
}
void iOCT_ECSModule_update() {
	iOCT_entityContext* array = (iOCT_entityContext*)iOCT_ECSModule_instance.contextPool.array;
	
	iOCT_entityContext* context;
	for (int index = 0; index < iOCT_ECSModule_instance.contextPool.count; index++) {
		context = &array[index];
		iOCT_entityContext_update(context);
	}
}