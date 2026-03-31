#pragma once
#include "ECS/types_internal.h"

#include "OCT_Math.h"
#include "cOCT_EngineStructure.h"

struct iOCT_physics2D {
	OCT_ID parentID;
	OCT_ID physicsID;

	OCT_ID transformID;

	float mass;
	OCT_vec2 lin_v;
	OCT_vec2 lin_a;
	OCT_vec2 lin_p;
	OCT_vec2 forceNet;

	float inertia;
	float ang_v;
	float ang_a;
	float ang_L;
	float torqueNet;

	float friction;
	float restitution;

};

OCT_ID iOCT_physics2D_add(iOCT_entityContext* context, OCT_ID entityID, float mass, float inertia, float friction, float restitution);