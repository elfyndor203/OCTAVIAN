#include "ECSModule_internal.h"
#include "ECS/entityContext/entityContext_internal.h"

#include "OCT_EngineStructure.h"
#include <stdlib.h>
#include <stdio.h>

OCT_module iOCT_ECSModule_instance = { 0 };

void OCT_ECSModule_init() {
	iOCT_ECSModule_init();
}
void iOCT_ECSModule_init() {
	OCT_module_init(&iOCT_ECSModule_instance, OCT_POOLSIZE_DEFAULT, sizeof(iOCT_entityContext));
}

void iOCT_ECSModule_free() {
	iOCT_entityContext* array = (iOCT_entityContext*)iOCT_ECSModule_instance.pool.array;

	for (int index = 0; index < iOCT_ECSModule_instance.pool.count; index++) {
		iOCT_entityContext* context = &array[index];
		iOCT_entityContext_close(context);
	}
	OCT_module_free(&iOCT_ECSModule_instance);
}