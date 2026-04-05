#pragma once
#include "_ECS_Output/_ECS_include.h"
#include "OCT_Math.h"

void iOCT_physPass_addGravity(_OCT_snapshot_physics* snapshot);
void iOCT_physPass_integrate(_OCT_snapshot_physics* snapshot);
void iOCT_physPass_finish(_OCT_snapshot_physics* snapshot);