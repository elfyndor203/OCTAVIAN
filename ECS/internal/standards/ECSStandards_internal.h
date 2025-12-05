#pragma once
#include "standards/ECSStandards.h"
#include "definitions/aliases_internal.h"
#include "definitions/APITypes_internal.h"

#define GENERIC_FAIL SIZE_MAX
#define iOCT_GET_FAILED GENERIC_FAIL

void* mallocCheck(size_t sizeToMalloc, const char* name); 




