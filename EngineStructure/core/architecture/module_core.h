#pragma once

#include "architecture/IDMap_core.h"
#include "architecture/pools_core.h"

struct iOCT_module {
	OCT_IDMap IDMap;
	iOCT_pool pool;
};

void iOCT_module_free(iOCT_module* instance);
void iOCT_module_init(iOCT_module* instance, OCT_counter capcity, size_t size);