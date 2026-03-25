#pragma once
#include "ECS/types_internal.h"

#include "OCT_Math.h"
#include "cOCT_EngineStructure.h"

struct iOCT_physics2D {
	OCT_ID parentID;
	OCT_ID physicsID;

	OCT_ID transformID;

	float m;
	OCT_vec2 v;
	OCT_vec2 a;
	OCT_vec2 p;

	float I; 
	float angV;
	float angA;
	OCT_vec2 angL;

	float friction;
	float restitution;
	OCT_vec2 forceNet;
	float torqueNet;
};

OCT_ID iOCT_physics2D_add(iOCT_entityContext* context, OCT_ID entityID, float mass, float inertia, float friction, float restitution);