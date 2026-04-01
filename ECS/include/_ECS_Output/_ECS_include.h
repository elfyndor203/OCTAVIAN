#pragma once
#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"
#include <stdbool.h>

#include "ECS/components/collider2D/collider2D.h"

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

//OCT_mat3 _OCT_transform2D_getMatrix(OCT_handle transformHandle);

OCT_vec4 _OCT_sprite2D_getUV(OCT_handle spriteHandle);
OCT_vec4 _OCT_sprite2D_getColor(OCT_handle spriteHandle);
OCT_vec2 _OCT_sprite2D_getDimensions(OCT_handle spriteHandle);

OCT_counter _OCT_entityContext_getCount();
OCT_counter _OCT_sprite2D_getCount(OCT_index contextIndex);
_OCT_sprite2D_snapshot _OCT_sprite2D_getSnapshot(OCT_index spriteIndex, OCT_index contextIndex);

_OCT_physics2D_snapshot* _OCT_physics2D_packSnapshot(OCT_index* outCount, OCT_ID* outContextRef, OCT_index contextIndex);
void _OCT_physics2D_writeBack(OCT_index count, OCT_ID contextID);