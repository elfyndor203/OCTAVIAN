#include "typeTable_internal.h"

#include "ECS/entity/entity_internal.h"

iOCT_VTable iOCT_ECSVTables[OCT_componentsTotal] = {
	[OCT_componentEntity] = iOCT_entity_VTable;
	[OCT_componentPosition2D] = 
}