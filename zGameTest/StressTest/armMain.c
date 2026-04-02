#include "arm.h"

#include "OCT_Engine.h"

#include <math.h>
#include <stdio.h>

#define DELTA_HISTORY 5

OCT_vec4 color_purple = { 0.5, 0.0, 0.5, 1.0 };
OCT_vec4 color_black = { 0.0, 0.0, 0.0, 0.5 };
OCT_vec2 normalRect = { 49, 27 };
OCT_vec2 normalSquare = { 20, 20 };

OCT_vec2 upRight = { 1, 1 };
OCT_vec2 downRight = { 1, -1 };
OCT_vec2 upLeft = { -1, 1 };
OCT_vec2 downLeft = { -1, -1 };

int main() {
	OCT_engine_start("The Ottoman Empire", 1920, 1080, color_black, 960 * 4, 540 * 4, 240, 100, 60);

	OCT_handle contextRoot;
	OCT_handle armContext = OCT_entityContext_open(&contextRoot);
	OCT_handle mouseRoot;
	OCT_handle mouseContext = OCT_entityContext_open(&mouseRoot);

	OCT_handle body = OCT_entity_new(armContext);
	OCT_handle extension = OCT_entity_new(body);
	OCT_physics2D_add(body, body, 1, 1, 3, 3, 0.8);

	OCT_handle armTex1 = OCT_image_load("images/hannes.png");
	OCT_handle armTex2 = OCT_image_load("images/anya.png");
	OCT_RENModule_flush();
	OCT_handle armLayer1 = OCT_layer_open(true, armTex1);
	OCT_handle armLayer2 = OCT_layer_open(true, armTex2);

	OCT_handle rightTopRoot;
	arm rightTopArm = spawnArm(10, body, armLayer1, normalRect, upRight, &rightTopRoot);
	OCT_handle rightBottomRoot;
	arm rightBottomArm = spawnArm(10, body, armLayer2, normalRect, downRight, &rightBottomRoot);
	OCT_handle leftTopRoot;
	arm leftTopArm = spawnArm(10, body, armLayer2, normalRect, upLeft, &leftTopRoot);
	OCT_handle leftBottomRoot;
	arm leftBottomArm = spawnArm(10, body, armLayer1, normalRect, downLeft, &leftBottomRoot);

	OCT_handle BrightTopRoot;
	arm BrightTopArm = spawnArm(10, extension, armLayer1, normalRect, upRight, &BrightTopRoot);
	OCT_handle BrightBottomRoot;
	arm BrightBottomArm = spawnArm(10, extension, armLayer2, normalRect, downRight, &BrightBottomRoot);
	OCT_handle BleftTopRoot;
	arm BleftTopArm = spawnArm(10, extension, armLayer2, normalRect, upLeft, &BleftTopRoot);

	OCT_handle BleftBottomRoot;
	arm BleftBottomArm = spawnArm(10, extension, armLayer1, normalRect, downLeft, &BleftBottomRoot);

	OCT_transform2D_moveBy(rightTopRoot, (OCT_vec2) { 50, 50 });
	OCT_transform2D_moveBy(rightBottomRoot, (OCT_vec2) { 50, -50 });
	OCT_transform2D_moveBy(leftTopRoot, (OCT_vec2) { -50, 50 });
	OCT_transform2D_moveBy(leftBottomRoot, (OCT_vec2) { -50, -50 });

	OCT_transform2D_moveBy(BrightTopRoot, (OCT_vec2) { 50, 50 });
	OCT_transform2D_moveBy(BrightBottomRoot, (OCT_vec2) { 50, -50 });
	OCT_transform2D_moveBy(BleftTopRoot, (OCT_vec2) { -50, 50 });
	OCT_transform2D_moveBy(BleftBottomRoot, (OCT_vec2) { -50, -50 });

	OCT_transform2D_rotateByDeg(extension, 90);

	/*OCT_handle extraArmRoot;
	arm extraArm = spawnArm(10, armContext, armLayer, normalRect, &extraArmRoot);
	OCT_transform2D_moveBy(extraArmRoot, (OCT_vec2) { -50, -150 });*/


	float rotateSpeed = 0.03;
	OCT_vec2 cursor;
	float curl = 1;
	OCT_handle newlySpawned = mouseRoot;
	bool mouseDown = false;
	bool mouseChanged = false;

	OCT_vec2 deltaHistory[DELTA_HISTORY] = { 0 };
	int deltaHead = 0;
	OCT_vec2 throwVelocity = { 0 };
	OCT_vec2 sum = { 0 };
	int count = 0;
	while (!OCT_window_closed()) {
		OCT_WDWModule_startFrame();
		cursor = OCT_cursorPos_read(true);

		// each frame, store current delta
		deltaHistory[deltaHead % DELTA_HISTORY] = OCT_cursorDelta_read(true);
		deltaHead++;

		if (OCT_keyState_read(OCT_KEY_UP) == OCT_KEYSTATE_DOWN) {
			rotateArm(rightTopArm, rotateSpeed, curl);
			rotateArm(rightBottomArm, -rotateSpeed, curl);
			rotateArm(leftTopArm, -rotateSpeed, curl);
			rotateArm(leftBottomArm, rotateSpeed, curl);

			rotateArm(BrightTopArm, rotateSpeed, curl);
			rotateArm(BrightBottomArm, -rotateSpeed, curl);
			rotateArm(BleftTopArm, -rotateSpeed, curl);
			rotateArm(BleftBottomArm, rotateSpeed, curl);

		}
		if (OCT_keyState_read(OCT_KEY_DOWN) == OCT_KEYSTATE_DOWN) {
			rotateArm(rightTopArm, -rotateSpeed, curl);
			rotateArm(rightBottomArm, rotateSpeed, curl);
			rotateArm(leftTopArm, rotateSpeed, curl);
			rotateArm(leftBottomArm, -rotateSpeed, curl);

			rotateArm(BrightTopArm, -rotateSpeed, curl);
			rotateArm(BrightBottomArm, rotateSpeed, curl);
			rotateArm(BleftTopArm, rotateSpeed, curl);
			rotateArm(BleftBottomArm, -rotateSpeed, curl);
		}

		if (OCT_keyState_read(OCT_KEY_MOUSE_LEFT) == OCT_KEYSTATE_DOWN) {
			if (!mouseDown) {
				mouseChanged = true;
				mouseDown = true;
			}
			else {
				mouseChanged = false;
			}
			OCT_transform2D_moveTo(body, cursor);
			OCT_physics2D_setVelocity(body, OCT_vec2_zero);
		}
		else {
			if (mouseDown) {
				mouseChanged = true;
				mouseDown = false;
			}
			else {
				mouseChanged = false;
			}
		}

		if (mouseChanged) {
			if (mouseDown) {
				printf("no grav\n");
				OCT_physics2D_setGravity(body, 0);
			}
			else {
				printf("grav\n");
				OCT_physics2D_setGravity(body, 1);
				// on release, average the history
				sum = OCT_vec2_zero;
				for (int i = 0; i < DELTA_HISTORY; i++) {
					if (deltaHistory[i].x != 0 || deltaHistory[i].y != 0) {
						sum = OCT_vec2_add(sum, deltaHistory[i]);
						count++;
					}
				}
				OCT_vec2 throwVelocity = count > 0 ? OCT_vec2_div(sum, count) : (OCT_vec2) { 0, 0 };
				printf("throw: %f %f\n", throwVelocity.x, throwVelocity.y);
				OCT_physics2D_addForce(body, OCT_vec2_mul(throwVelocity, 100));
			}
		}
		if (OCT_keyState_read(OCT_KEY_LEFT) == OCT_KEYSTATE_DOWN) {
			//OCT_physics2D_addVelocity(body, (OCT_vec2) { -0.001, 0 });
			OCT_physics2D_addForce(body, (OCT_vec2) { -0.1, 0 });

		}
		if (OCT_keyState_read(OCT_KEY_RIGHT) == OCT_KEYSTATE_DOWN) {
			OCT_physics2D_addForce(body, (OCT_vec2) { 0.1, 0 });

		}

		if (OCT_keyState_read(OCT_KEY_W) == OCT_KEYSTATE_DOWN) {
			OCT_physics2D_addForce(body, (OCT_vec2) { 0, 0.1 });
		}
		if (OCT_keyState_read(OCT_KEY_A) == OCT_KEYSTATE_DOWN) {
			OCT_physics2D_addForce(body, (OCT_vec2) { -0.05, 0 });
		}
		if (OCT_keyState_read(OCT_KEY_S) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(body, (OCT_vec2) { 0, -0.1 });
		}
		if (OCT_keyState_read(OCT_KEY_D) == OCT_KEYSTATE_DOWN) {
			OCT_physics2D_addForce(body, (OCT_vec2) { 0.05, 0 });
		}
		if (OCT_keyState_read(OCT_KEY_2) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_scaleBy(body, (OCT_vec2) { 1.000001, 1.000001 });
		}
		if (OCT_keyState_read(OCT_KEY_1) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_scaleBy(body, (OCT_vec2) { 0.999999, 0.999999 });
		}

		OCT_engine_tick();
	}
}