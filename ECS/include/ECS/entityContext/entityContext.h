#pragma once
#include "OCT_ECS.h"

OCT_entityHandle OCT_entityContext_open();
void OCT_entityContext_close(OCT_entityHandle rootHandle);
void OCT_entityContext_update(OCT_entityHandle root);

