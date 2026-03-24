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
OCT_vec2 normalRect = { 96, 54};

OCT_vec4 solid = { 1.0, 1.0, 1.0, 1.0 };
OCT_vec4 threeQSolid = { 1.0, 1.0, 1.0, 0.75 };
OCT_vec4 halfSolid = { 1.0, 1.0, 1.0, 0.5 };
OCT_vec4 quarterSolid = { 1.0, 1.0, 1.0, 0.25 };


int main() {
	OCT_WDWModule_init("OTTO OCTAvian that one guy that flew across the entire dungeon and then died", 1920, 1080, black);
	OCT_RESModule_init();
	OCT_RENModule_init((OCT_vec2){ 960, 540});
	OCT_ECSModule_init();


	OCT_handle mainContextRoot;
	OCT_handle mainContext = OCT_entityContext_open(&mainContextRoot);

	OCT_handle mainTex = OCT_image_load("ztestFiles/gear.png");
	OCT_RENModule_flush();
	OCT_handle layer = OCT_layer_open(true, mainTex);

	OCT_handle center = OCT_entity_new(mainContext);
	OCT_handle LB = OCT_entity_new(center);
	OCT_handle LT = OCT_entity_new(center);
	OCT_handle RT = OCT_entity_new(center);
	OCT_handle RB = OCT_entity_new(center);

	OCT_handle a = OCT_entity_new(center);
	OCT_handle b = OCT_entity_new(a);
	OCT_handle c = OCT_entity_new(b);
	OCT_handle d = OCT_entity_new(c);
	OCT_handle e = OCT_entity_new(d);
	OCT_handle f = OCT_entity_new(e);
	OCT_handle g = OCT_entity_new(f);
	OCT_handle h = OCT_entity_new(g);
	OCT_handle i = OCT_entity_new(h);
	OCT_handle j = OCT_entity_new(i);
	OCT_handle k = OCT_entity_new(j);
	OCT_handle l = OCT_entity_new(k);


	OCT_sprite2D_add(a, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(b, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(c, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(d, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(e, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(f, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(g, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(h, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(i, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(j, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(k, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(l, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);



	OCT_sprite2D_add(LB, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(LT, layer, threeQSolid, (OCT_vec4) { 0.0, 0.5, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(RT, layer, halfSolid, (OCT_vec4) { 0.5, 0.5, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(RB, layer, quarterSolid, (OCT_vec4) { 0.5, 0.0, 0.5, 0.5 }, normalRect);

	//OCT_transform2D_scaleBy(center, (OCT_vec2){0.5, 0.5});
	OCT_transform2D_moveBy(LB, (OCT_vec2) { -48.0, -27.0 });
	OCT_transform2D_moveBy(LT, (OCT_vec2) { -48.0, 27.0 });
	OCT_transform2D_moveBy(RT, (OCT_vec2) { 48.0, 27.0 });
	OCT_transform2D_moveBy(RB, (OCT_vec2) { 48.0, -27.0 });

	OCT_transform2D_moveBy(a, (OCT_vec2) { 5, -5.0 });
	OCT_transform2D_moveBy(b, (OCT_vec2) { 10, -10.0 });
	OCT_transform2D_moveBy(c, (OCT_vec2) { 15, -15.0 });
	OCT_transform2D_moveBy(d, (OCT_vec2) { 20, -20.0 });
	OCT_transform2D_moveBy(e, (OCT_vec2) { 25, -25.0 });
	OCT_transform2D_moveBy(f, (OCT_vec2) { 30.0, -30.0 });
	OCT_transform2D_moveBy(g, (OCT_vec2) { 35.0, -35.0 });
	OCT_transform2D_moveBy(h, (OCT_vec2) { 40.0, -40.0 });
	OCT_transform2D_moveBy(i, (OCT_vec2) { 45.0, -45.0 });
	OCT_transform2D_moveBy(j, (OCT_vec2) { 50.0, -50.0 });
	OCT_transform2D_moveBy(k, (OCT_vec2) { 55.0, -55.0 });
	OCT_transform2D_moveBy(l, (OCT_vec2) { 60.0, -60.0 });

	OCT_transform2D_scaleBy(center, (OCT_vec2) { 0.5, 0.5 });

	// OCT_transform2D_moveBy(RT, (OCT_vec2) { 5, 5 });

	float cycle = 0.0;
	float sine = 0;
	OCT_vec2 cursorPos;
	while (!OCT_window_closed()) {
		OCT_WDWModule_startFrame();

		cycle += 0.01f;
		sine = sinf(cycle) / 8;
		cursorPos = OCT_cursorPos_get(true);

		//printf("%f\n", sine);

		//OCT_transform2D_moveBy(center, (OCT_vec2) { 0, sinf(cycle) });

		/*OCT_transform2D_moveBy(LB, (OCT_vec2) { -sine, -sine });
		OCT_transform2D_moveBy(LT, (OCT_vec2) { -sine, sine });
		OCT_transform2D_moveBy(RB, (OCT_vec2) { sine, -sine });
		OCT_transform2D_moveBy(RT, (OCT_vec2) { sine, sine });*/

		if (OCT_keyState_read(OCT_KEY_W) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(center, (OCT_vec2) { 0, 1 });
		}
		if (OCT_keyState_read(OCT_KEY_A) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(center, (OCT_vec2) { -1, 0 });
		}
		if (OCT_keyState_read(OCT_KEY_S) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(center, (OCT_vec2) { 0, -1 });
		}
		if (OCT_keyState_read(OCT_KEY_D) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(center, (OCT_vec2) { 1, 0 });
		}
		if (OCT_keyState_read(OCT_KEY_RIGHT) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_rotateByDeg(center, -1);
		}
		if (OCT_keyState_read(OCT_KEY_LEFT) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_rotateByDeg(a, 0.1f);
			OCT_transform2D_rotateByDeg(b, 0.1f);
			OCT_transform2D_rotateByDeg(c, 0.1);
			OCT_transform2D_rotateByDeg(d, 0.1);
			OCT_transform2D_rotateByDeg(e, 0.1);
			OCT_transform2D_rotateByDeg(f, 0.1);
			OCT_transform2D_rotateByDeg(g, 0.1);
			OCT_transform2D_rotateByDeg(h, 0.1);
			OCT_transform2D_rotateByDeg(i, 0.1);
			OCT_transform2D_rotateByDeg(j, 0.1);
			OCT_transform2D_rotateByDeg(k, 0.1);
			OCT_transform2D_rotateByDeg(l, 0.1);
		}
		if (OCT_keyState_read(OCT_KEY_UP) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(LB, (OCT_vec2) { -0.1, -0.1 });
			OCT_transform2D_moveBy(LT, (OCT_vec2) { -0.1, 0.1 });
			OCT_transform2D_moveBy(RT, (OCT_vec2) { 0.1, 0.1 });
			OCT_transform2D_moveBy(RB, (OCT_vec2) { 0.1, -0.1 });
		}
		if (OCT_keyState_read(OCT_KEY_DOWN) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveBy(LB, (OCT_vec2) { 0.1, 0.1 });
			OCT_transform2D_moveBy(LT, (OCT_vec2) { 0.1, -0.1 });
			OCT_transform2D_moveBy(RT, (OCT_vec2) { -0.1, -0.1 });
			OCT_transform2D_moveBy(RB, (OCT_vec2) { -0.1, 0.1 });
		}

		if (OCT_keyState_read(OCT_KEY_MOUSE_MIDDLE) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveTo(center, (OCT_vec2) { 0, 0 });
		}

		if (OCT_keyState_read(OCT_KEY_MOUSE_LEFT) == OCT_KEYSTATE_UP) {
			OCT_transform2D_moveTo(center, cursorPos);
		}

		OCT_INPModule_update();
		OCT_ECSModule_update();
		OCT_RENModule_update();
		OCT_WDWModule_endFrame();


	};

	return 0;
}