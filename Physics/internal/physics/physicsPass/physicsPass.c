
#include "_ECS_Output/_ECS_include.h"
#include "OCT_Math.h"
#include <stdio.h>

#include "physics/dynamics/dynamics_internal.h"
#include "physics/collisions/collisions_internal.h"

void iOCT_physPass_calc(_OCT_snapshot_physics* snapshotPack, OCT_index count) {
	_OCT_snapshot_physics* snapshot;
	_OCT_snapshot_physics* collisionPhys;
	iOCT_collision collision;
	OCT_index physCt = 0;

	for (physCt = 0; physCt < count; physCt++) {
		snapshot = &snapshotPack[physCt];
		for (OCT_index collisCt = physCt + 1; collisCt < count; collisCt++) {
			collisionPhys = &snapshotPack[collisCt];
			collision = iOCT_physics_detectCollision(snapshot, collisionPhys);
			if (OCT_vec2_mag(collision.MTV) > 0) {
				printf("Collision between colliders %zu and %zu\n MTV: %f %f", collision.colliderA, collision.colliderB, collision.MTV.x, collision.MTV.y);
			}
		}
	}
	for (physCt = 0; physCt < count; physCt++) {
		snapshot = &snapshotPack[physCt];
		iOCT_physPass_addGravity(snapshot);
		iOCT_physPass_integrate(snapshot);
		iOCT_physPass_finish(snapshot);
	}
}