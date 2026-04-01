#pragma once
#include "types_core.h"
#include "core/types_internal.h"

#include "core/messaging/messaging_internal.h"
#include "messaging/messaging_core.h"

struct iOCT_COMModule {
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

extern iOCT_COMModule iOCT_COMModule_instance;

