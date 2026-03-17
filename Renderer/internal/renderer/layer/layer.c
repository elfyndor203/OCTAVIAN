#include "layer_internal.h"
#include "renderer/types_internal.h"

#include "OCT_EngineStructure.h"
#include <glad/glad.h>

#include "renderer/module/rendererModule_internal.h"
#include "renderer/rendererObject/rendererObject.h"
#include "renderer/spriteData/spriteData_internal.h"

OCT_ID iOCT_layer_open() {
	OCT_index newIndex;
	OCT_ID newID;
	iOCT_layer* newLayer;

	newLayer = (iOCT_layer*)OCT_pool_addTo(&iOCT_RENModule_instance.pool, &newIndex);
	newID = OCT_IDMap_register(&iOCT_RENModule_instance.IDMap, newIndex);

	newLayer->layerID = newID;
	newLayer->IDMap = OCT_IDMap_init(newID, OCT_POOLSIZE_DEFAULT);
	newLayer->renObjPool = OCT_pool_init(newID, OCT_POOLSIZE_DEFAULT, sizeof(iOCT_rendererObject));
	
	glGenBuffers(1, &newLayer->spriteBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, newLayer->spriteBuffer);
	glBufferData(GL_ARRAY_BUFFER, OCT_POOLSIZE_DEFAULT * sizeof(iOCT_spriteData), NULL, GL_DYNAMIC_DRAW);
	newLayer->spriteCapacity = OCT_POOLSIZE_DEFAULT;
}