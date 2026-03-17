#include "architecture/module.h"

#include "architecture/pools.h"
#include "architecture/IDMap.h"
#include "types.h"

void OCT_module_init(OCT_module* instance, size_t size) {
	instance->pool = OCT_pool_init(0, OCT_POOLSIZE_DEFAULT, size);
	instance->IDMap = OCT_IDMap_init(0, OCT_POOLSIZE_DEFAULT);
}

void OCT_module_free(OCT_module* instance) {
	OCT_pool_free(&instance->pool);
	OCT_IDMap_free(&instance->IDMap);
}