#pragma once

#include "architecture/IDMap_core.h"
#include "architecture/pools_core.h"

struct cOCT_module {
	cOCT_IDMap IDMap;
	cOCT_pool pool;
};

void iOCT_module_free(cOCT_module* instance);
void iOCT_module_init(cOCT_module* instance, OCT_counter capcity, size_t size);