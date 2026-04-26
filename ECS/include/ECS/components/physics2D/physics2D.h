#pragma once

#include "OCT_EngineStructure.h"

void OCT_physics2D_add(OCT_handle entity, OCT_handle rigidBodyOrigin, float gravity, float mass, float inertia, float friction, float restitution, bool isStatic);
OCT_vec2 OCT_physics2D_addVelocity(OCT_handle entityHandle, OCT_vec2 velocity);
void OCT_physics2D_setVelocity(OCT_handle entityHandle, OCT_vec2 velocity);
OCT_vec2 OCT_physics2D_readVelocity(OCT_handle entityHandle);
void OCT_physics2D_setGravity(OCT_handle entityHandle, float multiplier);
OCT_vec2 OCT_physics2D_addForce(OCT_handle entityHandle, OCT_vec2 force);
OCT_vec2 OCT_physics2D_addImpulse(OCT_handle entityHandle, OCT_vec2 impulse);
bool OCT_physics2D_isColliding(OCT_handle entityA, OCT_handle entityB);