#include "ECSModule_internal.h"

#include "ECS/entityContext/entityContext_internal.h"

iOCT_game_ECS* iOCT_startModule_ECS() {
	iOCT_game_ECS* ECS = malloc(sizeof(iOCT_game_ECS));
	ECS->entityContextPool = malloc(iOCT_ENTITYCONTEXT_DEFAULT_MAX, sizeof(iOCT_entityContext));	//	NOTE SET ALL VALUES TO NO_ENTITYCONTEXT
	ECS->entityContextMap = malloc(iOCT_ENTITYCONTEXT_DEFAULT_MAX, sizeof(OCT_index));
	ECS->entityContextCounter = 0;
	iOCT_ECS_active = ECS;	
	return ECS;
}

void iOCT_freeModule_ECS(iOCT_game_ECS* ECSModule) {
	for (int i = 0; i < ECSModule->entityContextCounter; i++) {
		iOCT_entityContext_close();
	}
	free(ECSModule);
}