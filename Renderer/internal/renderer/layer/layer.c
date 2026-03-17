#include "layer_internal.h"
#include "renderer/types_internal.h"

#include "OCT_EngineStructure.h"
#include <glad/glad.h>

#include "renderer/module/rendererModule_internal.h"
#include "renderer/rendererObject/rendererObject.h"
#include "renderer/spriteData/spriteData_internal.h"

iOCT_layer* iOCT_layer_get(OCT_ID layerID) {
	OCT_index index = iOCT_IDMap_getIndex(&iOCT_RENModule_instance.IDMap, layerID);
	return (iOCT_layer*)iOCT_pool_access(&iOCT_RENModule_instance.IDMap, index);
}

OCT_ID iOCT_layer_open(bool dynamic) {
	OCT_index newIndex;
	OCT_ID newID;
	iOCT_layer* newLayer;

	newLayer = (iOCT_layer*)iOCT_pool_addEntry(&iOCT_RENModule_instance.pool, &newIndex);
	newID = iOCT_IDMap_register(&iOCT_RENModule_instance.IDMap, newIndex);

	newLayer->layerID = newID;
	newLayer->IDMap = iOCT_IDMap_init(newID, OCT_POOLSIZE_DEFAULT);
	newLayer->renObjPool = iOCT_pool_init(newID, OCT_POOLSIZE_DEFAULT, sizeof(iOCT_rendererObject));
	newLayer->dynamic = dynamic;
	
	glGenBuffers(1, &newLayer->spriteBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, newLayer->spriteBuffer);
	glBufferData(GL_ARRAY_BUFFER, OCT_POOLSIZE_DEFAULT * sizeof(iOCT_spriteData), NULL, GL_DYNAMIC_DRAW);
	newLayer->spriteCapacity = OCT_POOLSIZE_DEFAULT;
}