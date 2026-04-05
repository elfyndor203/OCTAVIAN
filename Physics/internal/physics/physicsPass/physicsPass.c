
#include "_ECS_Output/_ECS_include.h"
#include "OCT_Math.h"

#include "physics/dynamics/dynamics_internal.h"

void iOCT_physPass_calc(_OCT_snapshot_physics* snapshotPack, OCT_index* count) {
	_OCT_snapshot_physics* snapshot;
	OCT_index physCt = 0;

	for (physCt = 0; physCt < count; physCt++) {
		snapshot = &snapshotPack[physCt];
		iOCT_physPass_addGravity(snapshot);
		iOCT_physPass_integrate(snapshot);
		iOCT_physPass_finish(snapshot);
	}
}