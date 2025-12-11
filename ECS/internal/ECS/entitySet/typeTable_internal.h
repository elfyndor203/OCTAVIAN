#pragma once
#include "OCT_EngineStructure.h"

typedef void* (*iOCT_getter)(OCT_entityHandle entityHandle);
typedef void* (*iOCT_allocator)(OCT_componentTypes componentType);

typedef struct iOCT_VTable {
	iOCT_getter get;
	iOCT_allocator allocate;
} iOCT_VTable;

extern iOCT_VTable iOCT_ECSVTables[OCT_componentsTotal];