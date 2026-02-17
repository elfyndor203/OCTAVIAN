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
	for (int index = 0; index < ECSModule->entityContextCounter; index++) {
		OCT_ID contextID = ECSModule->entityContextPool[index].entityContextID;
		iOCT_entityContext_close(contextID);
	}
	free(ECSModule);
}