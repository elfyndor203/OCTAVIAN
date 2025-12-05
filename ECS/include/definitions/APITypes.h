#pragma once
#include "standards/ECSStandards.h"
#include <stdint.h>

typedef size_t OCT_entitySetID;
typedef size_t OCT_entityID;

typedef struct OCT_entityHandle {
	OCT_entitySetID entitySetID;
	OCT_entityID entityID;
} OCT_entityHandle;