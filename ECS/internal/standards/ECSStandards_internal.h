#pragma once
#include "standards/ECSStandards.h"
#include "ECS/components/componentTypes/componentTypes_internal.h"


#define GENERIC_FAIL SIZE_MAX
#define GENERIC_NONE SIZE_MAX
#define iOCT_GET_FAILED GENERIC_FAIL

void* mallocCheck(size_t sizeToMalloc, const char* name); 




