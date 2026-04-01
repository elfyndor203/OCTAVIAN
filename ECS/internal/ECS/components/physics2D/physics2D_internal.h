#pragma once
#include "ECS/types_internal.h"

#include "OCT_Math.h"
#include "cOCT_EngineStructure.h"

#define iOCT_PHYSICS_RIGIDBODY_ORIGINDEPTH 1

struct iOCT_physics2D {
	OCT_ID parentID;
	OCT_ID physicsID;

	OCT_ID rbOriginID;	// physics component of the root of the rigidbody
	OCT_ID transformID;
	OCT_ID colliderID;

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

iOCT_physics2D* iOCT_physics2D_get(iOCT_entityContext* context, OCT_ID physicsID);
OCT_ID iOCT_physics2D_add(iOCT_entityContext* context, OCT_ID entityID, OCT_ID rigidBodyID, float mass, float inertia, float friction, float restitution);

OCT_vec2 iOCT_physics2D_addVelocity(iOCT_entityContext* context, OCT_ID physicsID, OCT_vec2 velocity);
OCT_vec2 iOCT_physics2D_addAcceleration(iOCT_entityContext* context, OCT_ID physicsID, OCT_vec2 acceleration);