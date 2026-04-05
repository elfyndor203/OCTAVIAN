#pragma once
#include "ECS/types_internal.h"

#include "OCT_Math.h"
#include "cOCT_EngineStructure.h"
#include <stdbool.h>

#define iOCT_PHYSICS_RIGIDBODY_ORIGINDEPTH 1

struct iOCT_physics2D {
	OCT_ID parentID;
	OCT_ID physicsID;

	OCT_ID rbOriginID;	// physics component of the root of the rigidbody
	OCT_ID transformID;
	OCT_ID colliderID;

	float mass;
	OCT_vec2 lin_v;
	OCT_vec2 forceNet;

	float inertia;
	float ang_v;
	float torqueNet;

	float friction;
	float restitution;
	float gravity;		// 1 = full gravity
	bool isStatic;
};

iOCT_physics2D* iOCT_physics2D_get(iOCT_entityContext* context, OCT_ID physicsID);
OCT_ID iOCT_physics2D_add(iOCT_entityContext* context, OCT_ID entityID, OCT_ID rigidBodyID, float gravity, float mass, float inertia, float friction, float restitution, bool isStatic);
OCT_vec2 iOCT_physics2D_addVelocity(iOCT_entityContext* context, OCT_ID physicsID, OCT_vec2 velocity);
void iOCT_physics2D_setVelocity(iOCT_entityContext* context, OCT_ID physicsID, OCT_vec2 velocity);
OCT_vec2 iOCT_physics2D_readVelocity(iOCT_entityContext* context, OCT_ID physicsID);
void iOCT_physics2D_setGravity(iOCT_entityContext* context, OCT_ID physicsID, float multiplier);
OCT_vec2 iOCT_physics2D_addForce(iOCT_entityContext* context, OCT_ID physicsID, OCT_vec2 force);
OCT_vec2 iOCT_physics2D_addImpulse(iOCT_entityContext* context, OCT_ID physicsID, OCT_vec2 impulse);