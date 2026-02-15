#pragma once
#include "OCT_Math.h"

#include "ECS/entityContext/entityContext_internal.h"

typedef struct iOCT_game_ECS {
	iOCT_entityContext* entityContextPool;
	OCT_index* entityContextMap;
	OCT_counter* entityContextCounter;
} iOCT_game_ECS;

iOCT_game_ECS* iOCT_ECS_active;	// Current running ECS