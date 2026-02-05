#pragma once
#include "standards/ECSStandards.h"
#include "OCT_Math.h"

#include "ECS/entityContext/entityContext_internal.h"

typedef struct iOCT_game_ECS {
	iOCT_entityContext* iOCT_entityContextPool;
	OCT_index* iOCT_entityContextMap;
	OCT_counter* iOCT_entityContextCounter;
} iOCT_game_ECS;

iOCT_game_ECS* iOCT_ECS_active;	// Current running ECS