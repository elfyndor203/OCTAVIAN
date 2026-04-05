#include "OCT_engine.h"
#include <stdio.h>

void wasdMove(OCT_handle entity, float speed) {
	if (OCT_keyState_read(OCT_KEY_W) == OCT_KEYSTATE_UP) {
		printf("w up\n");
		OCT_physics2D_setVelocity(entity, (OCT_vec2) { OCT_physics2D_readVelocity(entity).x, 0 });
		if (OCT_keyState_read(OCT_KEY_S) == OCT_KEYSTATE_HELD) {
			OCT_physics2D_addVelocity(entity, (OCT_vec2) { 0, speed });
		}
	}
	if (OCT_keyState_read(OCT_KEY_A) == OCT_KEYSTATE_UP) {
		OCT_physics2D_setVelocity(entity, (OCT_vec2) { 0, OCT_physics2D_readVelocity(entity).y });
		if (OCT_keyState_read(OCT_KEY_D) == OCT_KEYSTATE_HELD) {
			OCT_physics2D_addVelocity(entity, (OCT_vec2) { speed, 0 });
		}
	}
	if (OCT_keyState_read(OCT_KEY_S) == OCT_KEYSTATE_UP) {
		OCT_physics2D_setVelocity(entity, (OCT_vec2) { OCT_physics2D_readVelocity(entity).x, 0 });
		if (OCT_keyState_read(OCT_KEY_W) == OCT_KEYSTATE_HELD) {
			OCT_physics2D_addVelocity(entity, (OCT_vec2) { 0, speed });
		}
	}
	if (OCT_keyState_read(OCT_KEY_D) == OCT_KEYSTATE_UP) {
		OCT_physics2D_setVelocity(entity, (OCT_vec2) { 0, OCT_physics2D_readVelocity(entity).y });
		if (OCT_keyState_read(OCT_KEY_A) == OCT_KEYSTATE_HELD) {
			OCT_physics2D_addVelocity(entity, (OCT_vec2) { -speed, 0 });
		}
	}

	if (OCT_keyState_read(OCT_KEY_W) == OCT_KEYSTATE_DOWN) {
		OCT_physics2D_addVelocity(entity, (OCT_vec2) { 0, speed });
	}
	if (OCT_keyState_read(OCT_KEY_A) == OCT_KEYSTATE_DOWN) {
		OCT_physics2D_addVelocity(entity, (OCT_vec2) { -speed, 0 });
	}
	if (OCT_keyState_read(OCT_KEY_S) == OCT_KEYSTATE_DOWN) {
		OCT_physics2D_addVelocity(entity, (OCT_vec2) { 0, -speed });
	}
	if (OCT_keyState_read(OCT_KEY_D) == OCT_KEYSTATE_DOWN) {
		OCT_physics2D_addVelocity(entity, (OCT_vec2) { speed, 0 });
	}

	//if (OCT_keyState_read(OCT_KEY_W) == OCT_KEYSTATE_DOWN) {
	//	OCT_physics2D_addVelocity(entity, (OCT_vec2) { 0, speed });
	//}
	//if (OCT_keyState_read(OCT_KEY_A) == OCT_KEYSTATE_DOWN) {
	//	OCT_physics2D_addVelocity(entity, (OCT_vec2) { -speed, 0 });
	//}
	//if (OCT_keyState_read(OCT_KEY_S) == OCT_KEYSTATE_DOWN) {
	//	OCT_physics2D_addVelocity(entity, (OCT_vec2) { 0, -speed });
	//}
	//if (OCT_keyState_read(OCT_KEY_D) == OCT_KEYSTATE_DOWN) {
	//	OCT_physics2D_addVelocity(entity, (OCT_vec2) { speed, 0 });
	//}
}