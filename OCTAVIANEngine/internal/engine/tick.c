
#include "module/OCTModule_internal.h"
#include "OCT_Platform.h"
#include "OCT_Math.h"
#include "OCT_EngineStructure.h"
#include "OCT_Errors.h"
#include "OCT_ECS.h"
#include "OCT_Renderer.h"
#include "OCT_Resources.h"
#include "OCT_Window.h"
#include "OCT_Input.h"
#include "OCT_Physics.h"

void OCT_engine_startFrame() {
	OCT_WDWModule_poll();
	OCT_INPModule_update();
}

void OCT_engine_tick() {
	//OCT_WDWModule_startFrame;	// get window events

	OCT_PLTModule_update();  // update times
	iOCT_OCTModule_update(); // query times

	// ECS
	while (iOCT_OCTModule_instance.ECS_accumulator > iOCT_OCTModule_instance.ECS_tickTime) {
		OCT_ECSModule_update();
		iOCT_OCTModule_instance.ECS_accumulator -= iOCT_OCTModule_instance.ECS_tickTime;
	}
	// phyics
	while (iOCT_OCTModule_instance.PHY_accumulator > iOCT_OCTModule_instance.PHY_tickTime) {
		OCT_COMModule_update();
		OCT_PHYModule_update();

		iOCT_OCTModule_instance.PHY_accumulator -= iOCT_OCTModule_instance.PHY_tickTime;
	}

	// all rendering
	if (iOCT_OCTModule_instance.frameTime != 0) {
		while (iOCT_OCTModule_instance.FPS_accumulator > iOCT_OCTModule_instance.frameTime) {
			OCT_RENModule_update();
			OCT_WDWModule_update();

			iOCT_OCTModule_instance.FPS_accumulator -= iOCT_OCTModule_instance.frameTime;
		}
	}
	else {
		OCT_RENModule_update();
		OCT_WDWModule_update();
	}

}