#include "timer_internal.h"
#include "types_internal.h"

#include "module/PLTModule_internal.h"
#include <inttypes.h>

void iOCT_timer_init() {
	QueryPerformanceFrequency(&iOCT_PLTModule_instance.machineFreq);
	QueryPerformanceCounter(&iOCT_PLTModule_instance.prevFrameCt);
	QueryPerformanceCounter(&iOCT_PLTModule_instance.frameCt);
}

void iOCT_timer_update() {
	iOCT_PLTModule_instance.prevFrameCt = iOCT_PLTModule_instance.frameCt;
	QueryPerformanceCounter(&iOCT_PLTModule_instance.frameCt);
}

double OCT_timer_getDeltaTime() {
	return (double)(iOCT_PLTModule_instance.frameCt.QuadPart - iOCT_PLTModule_instance.prevFrameCt.QuadPart) / (double)(iOCT_PLTModule_instance.machineFreq.QuadPart);
}