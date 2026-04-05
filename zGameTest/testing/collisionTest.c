#include "OCT_engine.h"
#include "definitions.h"

#include <stdio.h>


int main() {
	OCT_engine_start("Sugar", 1920, 1080, color_black, 960, 540, 240, 120, 60);

	OCT_rect2 rect = {
	.height = 27,
	.width = 49,
	.origin = OCT_vec2_zero,
	.rotation = 0
	};
	OCT_shape2 collider = {
		.type = OCT_shapeType_rect2,
		.rect2 = rect
	};

	OCT_handle collisionRoot;
	OCT_handle collisionCtx = OCT_entityContext_open(&collisionRoot);

	OCT_handle gearTex = OCT_image_load("images/gear.png");
	OCT_RENModule_flush();
	OCT_handle foreGround = OCT_layer_open(true, gearTex);


	OCT_handle mainEntity = OCT_entity_new(collisionCtx);
	OCT_sprite2D_add(mainEntity, foreGround, solidColor, wholeTexture, normalRect);
	OCT_physics2D_add(mainEntity, mainEntity, 0, 3, 3, 4, 0.8);

	OCT_collider2D_add(mainEntity, collider);

	OCT_handle second = OCT_entity_new(collisionCtx);
	OCT_sprite2D_add(second, foreGround, solidColor, wholeTexture, normalRect);
	OCT_physics2D_add(second, second, 0, 3, 3, 4, 0.8);
	OCT_collider2D_add(second, collider);
	OCT_transform2D_moveBy(second, (OCT_vec2) { 30, 30 });

	OCT_vec2 cursor;
	while (!OCT_window_closed()) {
		OCT_WDWModule_startFrame();

		cursor = OCT_cursorPos_read(true);
		if (OCT_keyState_read(OCT_KEY_W) == OCT_KEYSTATE_DOWN) {
			OCT_physics2D_addForce(mainEntity, (OCT_vec2) { 0, 0.03 });
		}
		if (OCT_keyState_read(OCT_KEY_A) == OCT_KEYSTATE_DOWN) {
			OCT_physics2D_addForce(mainEntity, (OCT_vec2) { -0.03, 0 });
		}
		if (OCT_keyState_read(OCT_KEY_S) == OCT_KEYSTATE_DOWN) {
			OCT_physics2D_addForce(mainEntity, (OCT_vec2) { 0, -0.03 });
		}
		if (OCT_keyState_read(OCT_KEY_D) == OCT_KEYSTATE_DOWN) {
			OCT_physics2D_addForce(mainEntity, (OCT_vec2) { 0.03, 0 });
		}

		if (OCT_keyState_read(OCT_KEY_MOUSE_LEFT) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveTo(second, cursor);
			OCT_physics2D_setVelocity(second, OCT_vec2_zero);
		}

		OCT_engine_tick();
	}

	OCT_engine_stop();
}