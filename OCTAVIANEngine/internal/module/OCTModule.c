#include "OCTModule_internal.h"
#include "engine/tick.h"

#include "OCT_Platform.h"
#include <string.h>
#include <assert.h>

iOCT_OCTModule iOCT_OCTModule_instance = { 0 };

void iOCT_OCTModule_init(unsigned int maxFPS, unsigned int ECSHz, unsigned int physicsHz) {
	if (maxFPS == OCT_ENGINE_UNCAPPED_FPS) {
		iOCT_OCTModule_instance.frameTime = 0;
	}
	else {
		iOCT_OCTModule_instance.frameTime = 1.0 / maxFPS;
	}
	assert(physicsHz > 0 && ECSHz > 0);
	iOCT_OCTModule_instance.PHY_tickTime = 1.0 / physicsHz;
	iOCT_OCTModule_instance.ECS_tickTime = 1.0 / ECSHz;
}

void iOCT_OCTModule_update() {
	double deltaTime = OCT_timer_getDeltaTime();

	iOCT_OCTModule_instance.PHY_accumulator += deltaTime;
	iOCT_OCTModule_instance.ECS_accumulator += deltaTime;
	if (iOCT_OCTModule_instance.frameTime != 0) {
		iOCT_OCTModule_instance.FPS_accumulator += OCT_timer_getDeltaTime();
	}
}