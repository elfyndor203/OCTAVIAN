#include "rendererModule.h"
#include "renderer/types_internal.h"

#include "OCT_EngineStructure.h"

#include "renderer/layer/layer.h"

iOCT_module iOCT_RENModule_instance = { 0 };

void iOCT_RENModule_init() {
	iOCT_module_init(&iOCT_RENModule_instance, OCT_POOLSIZE_DEFAULT, sizeof(iOCT_layer));
}
void iOCT_RENModule_free() {
	iOCT_layer* array = (iOCT_layer*)iOCT_RENModule_instance.pool.array;

	for (int index = 0; index < iOCT_RENModule_instance.pool.count; index++) {
		iOCT_layer* layer = &array[index];
		iOCT_layer_close(layer);
	}
	iOCT_module_free(&iOCT_RENModule_instance);
}