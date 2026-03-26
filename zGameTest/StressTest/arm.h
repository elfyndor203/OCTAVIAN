#pragma once
#include "OCT_EngineStructure.h"
#include "OCT_Math.h"

typedef struct arm {
	OCT_handle* segmentList;
	size_t segmentCount;
} arm;

arm spawnArm(int count, OCT_handle context, OCT_handle layer, OCT_vec2 dimensions, OCT_vec2 direction, OCT_handle* outRoot);
void rotateArm(arm myArm, float rotation, float curlFactor);
void scaleArm(arm myArm, OCT_vec2 scale);