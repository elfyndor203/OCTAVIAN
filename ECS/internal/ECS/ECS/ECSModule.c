#include "ECSModule_internal.h"

iOCT_game_ECS* iOCT_startModule_ECS() {
	iOCT_game_ECS* ECS = malloc(sizeof(iOCT_game_ECS));
	ECS->iOCT_entityContextPool = calloc(iOCT_ENTITYCONTEXT_DEFAULT_MAX, sizeof(iOCT_entityContext));
	ECS->iOCT_entityContextMap = calloc(iOCT_ENTITYCONTEXT_DEFAULT_MAX, sizeof(OCT_index));
	ECS->iOCT_entityContextCounter = 0;
	iOCT_ECS_active = ECS;	
	return ECS;
}

void iOCT_freeModule_ECS(iOCT_game_ECS* ECSModule) {
	for (int i = 0; i < ECSModule->iOCT_entityContextCounter; i++) {
		iOCT_entityContext_close();
	}
	free(ECSModule);
}