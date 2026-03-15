#include "ECSModule_internal.h"
#include "ECS/entityContext/entityContext_internal.h"

#include "OCT_EngineStructure.h"
#include <stdlib.h>
#include <stdio.h>

iOCT_module_ECS iOCT_ECS_instance = { 0 };

void OCT_startModule_ECS() {
	iOCT_startModule_ECS();
}
void iOCT_startModule_ECS() {
	iOCT_ECS_instance.contextPool = OCT_pool_init(0, iOCT_ENTITYCONTEXT_DEFAULT_MAX, sizeof(iOCT_entityContext));
	iOCT_ECS_instance.IDMap = OCT_IDMap_init(0, iOCT_ENTITYCONTEXT_DEFAULT_MAX);
}

void iOCT_freeModule_ECS(iOCT_module_ECS* ECSModule) {
	iOCT_entityContext* array = (iOCT_entityContext*)ECSModule->contextPool.array;
	for (int index = 0; index < ECSModule->contextPool.count; index++) {
		iOCT_entityContext* context = &array[index];
		iOCT_entityContext_close(context);
	}
	free(ECSModule);
}