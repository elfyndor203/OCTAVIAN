#include "architecture/module_core.h"
#include "linking/types_core.h"

#include "architecture/pools_core.h"
#include "architecture/IDMap_core.h"

void iOCT_module_init(cOCT_module* instance, OCT_counter capacity, size_t size) {
	instance->pool = cOCT_pool_init(0, capacity, size);
	instance->IDMap = cOCT_IDMap_init(0, capacity);
}

void iOCT_module_free(cOCT_module* instance) {
	cOCT_pool_free(&instance->pool);
	cOCT_IDMap_free(&instance->IDMap);
}