#pragma once
#include "types_internal.h"

#include <Windows.h>
#include <inttypes.h>

struct iOCT_PLTModule {
	LARGE_INTEGER machineFreq;
	LARGE_INTEGER prevFrameCt;
	LARGE_INTEGER frameCt;
};

extern iOCT_PLTModule iOCT_PLTModule_instance;
