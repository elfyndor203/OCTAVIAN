#include "architecture/module.h"

#include "architecture/pools.h"
#include "architecture/IDMap.h"
#include "types.h"

void OCT_module_start(OCT_module* instance, size_t size) {
	instance->pool = OCT_pool_init(0, OCT_POOLSIZE_DEFAULT, size);
	instance->IDMap = OCT_IDMap_init(0, OCT_POOLSIZE_DEFAULT);
}

void OCT_module_free(OCT_module* instance) {
	void* array = instance->pool.array;
	for (int index = 0; index < instance->pool.count; index++) {
		iOCT_entityContext* context = &array[index];
		iOCT_entityContext_close(context);
	}
	OCT_pool_free(&instance->pool);
	OCT_IDMap_free
}