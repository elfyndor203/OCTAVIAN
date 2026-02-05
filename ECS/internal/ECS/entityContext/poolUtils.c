#include "entitySet_internal.h"
#include "standards/ECSStandards_internal.h"

#include <stdbool.h>

#define iOCT_POOL_FULLBUFFER 1

bool iOCT_pool_full(iOCT_entityContext* entityCtx, OCT_componentTypes componentType) {
	if (entityCtx->pools[componentType].counter == entityCtx->pools[componentType].capacity - iOCT_POOL_FULLBUFFER) {
		return true;
	}
	else {
		return false;
	}
}

OCT_index iOCT_pool_nextIndex(iOCT_entityContext* entityCtx, OCT_componentTypes componentType) {
	OCT_index index = entityCtx->pools[componentType].counter;
	entityCtx->pools[componentType].counter += 1;
	return index;
}

