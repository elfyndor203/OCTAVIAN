#include "architecture/module_core.h"
#include "linking/types_core.h"

#include "architecture/pools_core.h"
#include "architecture/IDMap_core.h"

void iOCT_module_init(iOCT_module* instance, OCT_counter capacity, size_t size) {
	instance->pool = iOCT_pool_init(0, OCT_POOLSIZE_DEFAULT, size);
	instance->IDMap = iOCT_IDMap_init(0, OCT_POOLSIZE_DEFAULT);
}

void iOCT_module_free(iOCT_module* instance) {
	iOCT_pool_free(&instance->pool);
	iOCT_IDMap_free(&instance->IDMap);
}