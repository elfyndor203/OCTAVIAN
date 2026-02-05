#include "ECSModule_internal.h"

iOCT_game_ECS* iOCT_startModule_ECS() {
	iOCT_game_ECS* ECS = malloc(sizeof(iOCT_game_ECS));
	ECS->iOCT_entityContextPool = calloc(iOCT_ENTITYCONTEXT_DEFAULT_MAX, sizeof(iOCT_entityContext));
	ECS->iOCT_entityContextMap = calloc(iOCT_ENTITYCONTEXT_DEFAULT_MAX, sizeof(OCT_index));
	ECS->iOCT_entityContextCounter = 0;
	return ECS;
}