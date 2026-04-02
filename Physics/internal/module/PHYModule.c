#include "PHYModule_internal.h"
#include "physics/types_internal.h"

#include "_ECS_Output/_ECS_include.h"
#include "cOCT_Communication.h"

#include "physics/physicsPass/physicsPass_internal.h"

iOCT_PHYModule iOCT_PHYModule_instance = { 0 };

void OCT_PHYModule_init(OCT_vec2 gravity, unsigned int hz) {
	iOCT_PHYModule_instance.gravity = gravity;
	iOCT_PHYModule_instance.deltaT = 1.0 / hz;
}
void OCT_PHYModule_update() {
	OCT_index contextCt = _OCT_entityContext_getCount();

	OCT_ID contextID;
	OCT_index physCount;
	_OCT_physics2D_snapshot* snapshotPack;
	for (OCT_index i = 0; i < contextCt; i++) {
		snapshotPack = _OCT_physics2D_packSnapshot(&physCount, &contextID, i);
		
		iOCT_physPass_calc(snapshotPack, physCount);

		_OCT_physics2D_writeBack(physCount, contextID);
	}
}