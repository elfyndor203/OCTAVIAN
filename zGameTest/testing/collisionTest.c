#include "definitions.h"
#include "wasd.h"

#include "OCT_engine.h"

#include <stdio.h>

#define MOVEMENT_SPEED 3

int main() {
	OCT_engine_start("Henry Sugar", 1920, 1080, color_black, 960, 540, 240, 120, 120);

	OCT_shape2 entityCollider = {
		.type = OCT_shapeType_rect2,
		.rect2 = {
			.height = 27,
			.width = 49,
			.origin = OCT_vec2_zero,
			.rotation = 0
		}
	};
	OCT_shape2 platformCollider = {
		.type = OCT_shapeType_rect2,
		.rect2 = {
			.height = 30,
			.width = 1000,
			.rotation = 0,
			.origin = (OCT_vec2){0, 0}
			}
	};

	OCT_handle collisionRoot;
	OCT_handle collisionCtx = OCT_entityContext_open(&collisionRoot);

	OCT_handle gearTex = OCT_image_load("images/gear.png");
	OCT_handle hannesTex = OCT_image_load("images/hannes.png");
	OCT_handle anyaTex = OCT_image_load("images/anya.png");
	OCT_RENModule_flush();
	OCT_handle foreGround = OCT_layer_open(true, gearTex);
	OCT_handle platforms = OCT_layer_open(true, hannesTex);
	OCT_handle anya = OCT_layer_open(true, anyaTex);

	OCT_handle mainEntity = OCT_entity_new(collisionCtx);
	OCT_sprite2D_add(mainEntity, foreGround, solidColor, wholeTexture, normalRect);
	OCT_physics2D_add(mainEntity, mainEntity, 1.0, 3, 3, 4, 0, false);
	OCT_collider2D_add(mainEntity, entityCollider);

	OCT_handle random = OCT_entity_new(collisionCtx);
	OCT_sprite2D_add(random, anya, solidColor, wholeTexture, normalRect);
	OCT_physics2D_add(random, random, 1.0, 3, 3, 4, 0, false);
	OCT_collider2D_add(random, entityCollider);
	OCT_transform2D_moveBy(random, (OCT_vec2) { 0, 50 });

	OCT_handle second = OCT_entity_new(collisionCtx);
	OCT_sprite2D_add(second, platforms, solidColor, wholeTexture, (OCT_vec2) {960, 30});
	OCT_physics2D_add(second, second, 0, 30, 3, 4, 0, true);
	OCT_collider2D_add(second, platformCollider);
	OCT_transform2D_moveBy(second, (OCT_vec2) { 0, -100 });

	OCT_vec2 cursor;
	while (!OCT_window_closed()) {
		OCT_engine_startFrame();

		cursor = OCT_cursorPos_read(true);

		wasdMove(mainEntity, MOVEMENT_SPEED);

		if (OCT_keyState_read(OCT_KEY_SPACE) == OCT_KEYSTATE_DOWN) {
			OCT_physics2D_addImpulse(mainEntity, (OCT_vec2) { 0, 30.0 });
		}
		if (OCT_keyState_read(OCT_KEY_MOUSE_LEFT) == OCT_KEYSTATE_HELD) {
			OCT_transform2D_moveTo(random, cursor);
			OCT_physics2D_setVelocity(random, OCT_vec2_zero);
		}

		OCT_engine_tick();
	}

	OCT_engine_stop();
}