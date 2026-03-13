#include "ECSModule_internal.h"
#include "ECS/entityContext/entityContext_internal.h"
#include <stdlib.h>
#include <stdio.h>

iOCT_manager_ECS iOCT_ECS_instance = { 0 };

void OCT_startModule_ECS() {
	iOCT_startModule_ECS();
}
void iOCT_startModule_ECS() {
	iOCT_ECS_instance.entityContextPool = malloc(iOCT_ENTITYCONTEXT_DEFAULT_MAX * sizeof(iOCT_entityContext));	//	NOTE SET ALL VALUES TO NO_ENTITYCONTEXT
	if (!iOCT_ECS_instance.entityContextPool) {
		printf("fail 1");
	}
	iOCT_ECS_instance.entityContextMap = malloc(iOCT_ENTITYCONTEXT_DEFAULT_MAX * sizeof(OCT_index));
	if (!iOCT_ECS_instance.entityContextMap) {
		printf("fail 2");
	}
	iOCT_ECS_instance.entityContextCounter = 0;
}

void iOCT_freeModule_ECS(iOCT_manager_ECS* ECSModule) {
	for (int index = 0; index < ECSModule->entityContextCounter; index++) {
		iOCT_entityContext* context = &ECSModule->entityContextPool[index];
		iOCT_entityContext_close(context);
	}
	free(ECSModule);
}