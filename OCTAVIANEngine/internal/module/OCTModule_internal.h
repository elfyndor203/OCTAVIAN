#pragma once
#include "types_internal.h"

#include "OCT_Math.h"

struct iOCT_OCTModule {
	double ECS_accumulator;
	double PHY_accumulator;
	double FPS_accumulator;

	double PHY_tickTime;
	double ECS_tickTime;
	double frameTime;
};

extern iOCT_OCTModule iOCT_OCTModule_instance;
void iOCT_OCTModule_init(unsigned int maxFPS, unsigned int ECSHz, unsigned int physicsHz);
void iOCT_OCTModule_update();