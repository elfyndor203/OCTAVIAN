#include "PLTModule_internal.h"
#include "types_internal.h"

#include "timer/timer_internal.h"

iOCT_PLTModule iOCT_PLTModule_instance = { 0 };

void OCT_PLTModule_init() {
	iOCT_timer_init();
}

void OCT_PLTModule_update() {
	iOCT_timer_update();
}