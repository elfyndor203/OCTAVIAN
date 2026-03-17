#pragma once

#include "IDMap.h"
#include "pools.h"

struct OCT_module {
	OCT_IDMap IDMap;
	OCT_pool pool;
};

void OCT_module_free(OCT_module* instance);
void OCT_module_init(OCT_module* instance, size_t size);
