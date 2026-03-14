#include "OCT_EngineStructure.h"

const OCT_ID OCT_errorID = SIZE_MAX;

OCT_engineHandle _OCT_active = { SIZE_MAX - 1, SIZE_MAX - 1};
OCT_engineHandle _OCT_errorHandle = { SIZE_MAX, SIZE_MAX };
