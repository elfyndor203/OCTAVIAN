#pragma once
#include "OCT_Math.h"
#include "OCT_EngineStructure.h"
#include <stdbool.h>

typedef struct {
	bool visible;
	OCT_mat3 transform;
	OCT_vec4 uv;
	OCT_vec4 color;
	OCT_vec2 dimensions;
	OCT_handle layer;
} _OCT_snapshot_sprite;

typedef struct {
	OCT_ID physicsID;		// return identifiers
	OCT_ID transformID;
	OCT_ID colliderID;

	OCT_index rbOriginIndex;	// rigid body grouping

	float mass;			// properties
	OCT_vec2 lin_v;
	OCT_vec2 forceNet;
	float inertia;
	float ang_v;
	float torqueNet;
	float friction;
	float restitution;
	float gravity;		// 1 = full gravity
	bool isStatic;

	OCT_vec2 position;	// state
	OCT_vec2 scale;
	float rotation;

	OCT_shape2 collider;
} _OCT_snapshot_physics;