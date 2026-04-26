#include "COMModule_internal.h"

#include "core/types_internal.h"
#include <string.h>

#include "core/messaging/messaging_internal.h"
iOCT_COMModule iOCT_COMModule_instance = { 0 };

void OCT_COMModule_update() {
	iOCT_eventBox_clear(&iOCT_COMModule_instance.eventBox_ECS);
	iOCT_eventBox_clear(&iOCT_COMModule_instance.eventBox_REN);
	iOCT_eventBox_clear(&iOCT_COMModule_instance.eventBox_RES);
	iOCT_eventBox_clear(&iOCT_COMModule_instance.eventBox_WDW);
	iOCT_eventBox_clear(&iOCT_COMModule_instance.eventBox_INP);
	iOCT_eventBox_clear(&iOCT_COMModule_instance.eventBox_PHY);
}