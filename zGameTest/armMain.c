#include "arm.h"

#include "OCT_Math.h"
#include "OCT_EngineStructure.h"
#include "OCT_Errors.h"
#include "OCT_ECS.h"
#include "OCT_Renderer.h"
#include "OCT_Resources.h"
#include "OCT_window.h"
#include "OCT_Input.h"

#include <math.h>

OCT_vec4 purple = { 0.5, 0.0, 0.5, 1.0 };
OCT_vec4 black = { 0.0, 0.0, 0.0, 0.5 };
OCT_vec2 normalRect = { 49, 27 };
OCT_vec2 normalSquare = { 20, 20 };

OCT_vec2 upRight = { 1, 1 };
OCT_vec2 downRight = { 1, -1 };
OCT_vec2 upLeft = { -1, 1 };
OCT_vec2 downLeft = { -1, -1 };

int main() {
	OCT_WDWModule_init("Arms", 1920, 1080, black);
	OCT_RESModule_init();
	OCT_RENModule_init((OCT_vec2) { 960, 540 });
	OCT_ECSModule_init();

	OCT_handle contextRoot;
	OCT_handle armContext = OCT_entityContext_open(&contextRoot);

	OCT_handle body = OCT_entity_new(armContext);

	OCT_handle armTex1 = OCT_image_load("ztestFiles/hannes.png");
	OCT_handle armTex2 = OCT_image_load("ztestFiles/anya.png");
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

	OCT_transform2D_moveBy(rightTopRoot, (OCT_vec2) { 50, 50 });
	OCT_transform2D_moveBy(rightBottomRoot, (OCT_vec2) { 50, -50 });
	OCT_transform2D_moveBy(leftTopRoot, (OCT_vec2) { -50, 50 });
	OCT_transform2D_moveBy(leftBottomRoot, (OCT_vec2) { -50, -50 });

	/*OCT_handle extraArmRoot;
	arm extraArm = spawnArm(10, armContext, armLayer, normalRect, &extraArmRoot);
	OCT_transform2D_moveBy(extraArmRoot, (OCT_vec2) { -50, -150 });*/


	float rotateSpeed = 0.03;
	OCT_vec2 cursor;
	float curl = 1;
	while (!OCT_window_closed()) {
		OCT_WDWModule_startFrame();
		cursor = OCT_cursorPos_read(true);

		if (OCT_keyState_read(OCT_KEY_UP) == OCT_KEYSTATE_DOWN) {
			rotateArm(rightTopArm, rotateSpeed, curl);
			rotateArm(rightBottomArm, -rotateSpeed, curl);
			rotateArm(leftTopArm, -rotateSpeed, curl);
			rotateArm(leftBottomArm, rotateSpeed, curl);

		}
		if (OCT_keyState_read(OCT_KEY_DOWN) == OCT_KEYSTATE_DOWN) {
			rotateArm(rightTopArm, -rotateSpeed, curl);
			rotateArm(rightBottomArm, rotateSpeed, curl);
			rotateArm(leftTopArm, rotateSpeed, curl);
			rotateArm(leftBottomArm, -rotateSpeed, curl);
		}

		if (OCT_keyState_read(OCT_KEY_MOUSE_LEFT) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveTo(body, cursor);
		}

		if (OCT_keyState_read(OCT_KEY_LEFT) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_rotateByDeg(body, 0.1);
		}
		if (OCT_keyState_read(OCT_KEY_RIGHT) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_rotateByDeg(body, -0.1);
		}

		if (OCT_keyState_read(OCT_KEY_W) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(body, (OCT_vec2){ 0, 0.1 });
		}
		if (OCT_keyState_read(OCT_KEY_A) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(body, (OCT_vec2) { -0.1, 0 });
		}
		if (OCT_keyState_read(OCT_KEY_S) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(body, (OCT_vec2) { 0, -0.1 });
		}
		if (OCT_keyState_read(OCT_KEY_D) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(body, (OCT_vec2) { 0.1, 0 });
		}
		if (OCT_keyState_read(OCT_KEY_2) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_scaleBy(body, (OCT_vec2) {1.001, 1.001});
		}
		if (OCT_keyState_read(OCT_KEY_1) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_scaleBy(body, (OCT_vec2) { 0.999, 0.999 });
		}
		
		OCT_INPModule_update();
		OCT_ECSModule_update();
		OCT_RENModule_update();
		OCT_WDWModule_endFrame();
	}
}