#pragma once
#include "OCT_Math.h"
#include "OCT_EngineStructure.h"

typedef struct {
	bool visible;
	OCT_mat3 transform;
	OCT_vec4 uv;
	OCT_vec4 color;
	OCT_vec2 dimensions;
	OCT_handle layer;
} _OCT_sprite2D_snapshot;

typedef struct {
	OCT_ID physicsID;
	OCT_ID transformID;
	OCT_index rbOriginIndex;

	float mass;
	OCT_vec2 lin_v;
	OCT_vec2 forceNet;
	float inertia;
	float ang_v;
	float torqueNet;
	float friction;
	float restitution;

	float gravity; // 1 = full gravity
	OCT_vec2 position;
	float rotation;

	OCT_shapes collider;
} _OCT_physics2D_snapshot;