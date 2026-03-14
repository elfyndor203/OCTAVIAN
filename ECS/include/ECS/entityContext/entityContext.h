#pragma once
#include "OCT_ECS.h"

OCT_handle OCT_entityContext_open();
void OCT_entityContext_close(OCT_handle rootHandle);
void OCT_entityContext_update(OCT_handle root);

