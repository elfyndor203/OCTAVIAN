#pragma once
#include "physics/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "cOCT_Communication.h"
#include "OCT_Math.h"

struct iOCT_collision {
	OCT_ID colliderA;
	OCT_ID colliderB;
	OCT_vec2 MTV;
};

extern iOCT_collision iOCT_collision_none;