#include "collisions_internal.h"
#include "physics/types_internal.h"

#include "cOCT_Communication.h"
#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

static OCT_vec2 iOCT_physics_project(OCT_vec2 axis, OCT_vec2* verts, OCT_index count);
static float iOCT_physics_projOverlap(OCT_vec2 projA, OCT_vec2 projB);

iOCT_collision iOCT_collision_none = { OCT_handle_NULL, OCT_handle_NULL, 0.0f, 0.0f };

iOCT_collision iOCT_physics_detectCollision(_OCT_snapshot_physics* physA, _OCT_snapshot_physics* physB) {
	iOCT_collision collision = iOCT_collision_none;
	float radiusA;
	float radiusB;

	if (physA->rbOriginIndex == physB->rbOriginIndex) {	// if they belong to the same rigidbody
		return iOCT_collision_none;
	}

	if (physA->collider.type == OCT_shapeType_rect2 && physB->collider.type == OCT_shapeType_rect2) {	// check radii
		OCT_rect2 rectA = physA->collider.rect2;
		OCT_rect2 rectB = physB->collider.rect2;
		radiusA = OCT_vec2_mag(OCT_rect2_getVerts(physA->collider.rect2, NULL, NULL, NULL));
		radiusB = OCT_vec2_mag(OCT_rect2_getVerts(physB->collider.rect2, NULL, NULL, NULL));

		if (OCT_vec2_mag(OCT_vec2_sub(rectA.origin, rectB.origin)) > (radiusA + radiusB)) {	// too far apart
			return iOCT_collision_none;
		}

		collision.colliderA = physA->colliderID;
		collision.colliderB = physB->colliderID;
		collision.MTV = iOCT_physics_SAT2Rect2(rectA, rectB);
	}

	if (OCT_vec2_equal(collision.MTV, OCT_vec2_zero, epsilon)) {
		return iOCT_collision_none;
	}
	else {
		return collision;
	}
}

static OCT_vec2 iOCT_physics_SAT2Rect2(OCT_rect2 rectA, OCT_rect2 rectB) {
	OCT_vec2 vertsA[4];	// vertices to project
	OCT_vec2 vertsB[4];
	vertsA[0] = OCT_rect2_getVerts(rectA, &vertsA[1], &vertsA[2], &vertsA[3]);
	vertsB[0] = OCT_rect2_getVerts(rectB, &vertsB[1], &vertsB[2], &vertsB[3]);

	OCT_vec2 axesA[2];	// projection axes
	OCT_vec2 axesB[2];
	axesA[0] = OCT_rect2_getNormals(rectA, &axesA[1]);
	axesB[0] = OCT_rect2_getNormals(rectB, &axesB[1]);

	OCT_vec2 projA;
	OCT_vec2 projB;
	float overlap;
	float minOverlap = FLT_MAX;
	OCT_vec2 minAxis = OCT_vec2_zero; // guaranteed to be set at some point
	OCT_vec2 MTV;
	for (int axisA = 0; axisA < 2; axisA++) {		// for each axis of A
		projA = iOCT_physics_project(axesA[axisA], vertsA, 4);
		projB = iOCT_physics_project(axesA[axisA], vertsB, 4);
		overlap = iOCT_physics_projOverlap(projA, projB);
		if (overlap <= 0) {			// if no overlap, no collision
			return OCT_vec2_zero;
		}
		if (overlap < minOverlap) {
			minOverlap = overlap;
			minAxis = axesA[axisA];
		}
	}
	for (int axisB = 0; axisB < 2; axisB++) {		// for each axis of B
		projA = iOCT_physics_project(axesB[axisB], vertsA, 4);
		projB = iOCT_physics_project(axesB[axisB], vertsB, 4);
		overlap = iOCT_physics_projOverlap(projA, projB);
		if (overlap <= 0) {
			return OCT_vec2_zero;
		}
		if (overlap < minOverlap) {
			minOverlap = overlap;
			minAxis = axesB[axisB];
		}
	}

	OCT_vec2 direction = OCT_vec2_sub(rectA.origin, rectB.origin);
	if (OCT_vec2_dot(direction, minAxis) < 0) {
		minAxis = OCT_vec2_neg(minAxis);
	}
	MTV = OCT_vec2_mul(minAxis, minOverlap);
	return MTV;
}

#pragma region helpers
static OCT_vec2 iOCT_physics_project(OCT_vec2 axis, OCT_vec2* verts, OCT_index count) {
	float min = OCT_vec2_dot(axis, verts[0]);
	float max = min;
	
	float proj;
	for (int v = 1; v < count; v++) {
		proj = OCT_vec2_dot(axis, verts[v]);
		if (proj < min) {
			min = proj;
		}
		else if (proj > max) {
			max = proj;
		}
	}

	return (OCT_vec2) { min, max };
}

static float iOCT_physics_projOverlap(OCT_vec2 projA, OCT_vec2 projB) {
	float overlap = fminf(projA.y, projB.y) - fmaxf(projA.x, projB.x);
	if (overlap <= 0) {
		return 0;
	}
	else {
		return overlap;
	}
}
#pragma endregion
