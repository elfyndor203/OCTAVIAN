
#include "_ECS_Output/_ECS_include.h"
#include "OCT_EngineStructure.h"
#include "OCT_Math.h"

void iOCT_physPass_kinematics(_OCT_physics2D_snapshot* data, OCT_index count) {
	_OCT_physics2D_snapshot* snapshot;
	for (OCT_index i = 0; i < count; i++) {
		snapshot = &data[i];
		snapshot->lin_v = OCT_vec2_add(snapshot->lin_v, snapshot->lin_a);
		snapshot->position = OCT_vec2_add(snapshot->position, snapshot->lin_v);
	}
}