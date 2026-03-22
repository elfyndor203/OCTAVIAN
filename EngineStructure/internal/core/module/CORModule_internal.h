#pragma once
#include "core/types_internal.h"

#include "cOCT_EngineStructure.h"

struct iOCT_CORModule {
	cOCT_messageBox inbox_ECS;
	cOCT_messageBox inbox_REN;
	cOCT_messageBox inbox_RES;
	cOCT_messageBox inbox_WDW;
	cOCT_messageBox inbox_INP;

	cOCT_messageBox eventBox_ECS;
	cOCT_messageBox eventBox_REN;
	cOCT_messageBox eventBox_RES;
	cOCT_messageBox eventBox_WDW;
	cOCT_messageBox eventBox_INP;
};

extern iOCT_CORModule iOCT_CORModule_instance;

