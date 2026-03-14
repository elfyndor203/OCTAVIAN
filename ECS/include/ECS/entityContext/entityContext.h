#pragma once
#include "OCT_ECS.h"

OCT_engineHandle OCT_entityContext_open();
void OCT_entityContext_close(OCT_engineHandle rootHandle);
void OCT_entityContext_update(OCT_engineHandle root);

