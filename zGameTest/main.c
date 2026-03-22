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
OCT_vec2 normalRect = { 96, 54 };

int main() {
	OCT_WDWModule_init("OTTO OCTAvian that one guy that flew across the entire dungeon and then died", 1920, 1080, black);
	OCT_RESModule_init();
	OCT_RENModule_init((OCT_vec2){ 960, 540});
	OCT_ECSModule_init();

	OCT_vec4 solid = { 1.0, 1.0, 1.0, 1.0 };

	OCT_handle mainContextRoot;
	OCT_handle mainContext = OCT_entityContext_open(&mainContextRoot);

	OCT_handle mainTex = OCT_image_load("C:/Users/Elfyndor/MyDocuments/Projects/OCTAVIAN/zGameTest/zTestFiles/gear.png");
	OCT_RENModule_flush();
	OCT_handle layer = OCT_layer_open(true, mainTex);

	OCT_handle center = OCT_entity_new(mainContext);
	OCT_handle LB = OCT_entity_new(center);
	OCT_handle LT = OCT_entity_new(center);
	OCT_handle RT = OCT_entity_new(center);
	OCT_handle RB = OCT_entity_new(center);

	OCT_sprite2D_add(LB, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(LT, layer, solid, (OCT_vec4) { 0.0, 0.5, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(RT, layer, solid, (OCT_vec4) { 0.5, 0.5, 0.5, 0.5 }, normalRect);
	OCT_sprite2D_add(RB, layer, solid, (OCT_vec4) { 0.5, 0.0, 0.5, 0.5 }, normalRect);

	OCT_transform2D_moveBy(LB, (OCT_vec2) { -48.0, -27.0 });
	OCT_transform2D_moveBy(LT, (OCT_vec2) { -48.0, 27.0 });
	OCT_transform2D_moveBy(RT, (OCT_vec2) { 48.0, 27.0 });
	OCT_transform2D_moveBy(RB, (OCT_vec2) { 48.0, -27.0 });

	float cycle = 2.0;
	float sine = 0;
	while (!OCT_window_closed()) {

		cycle += 0.1f;
		sine = sinf(cycle);

		//OCT_transform2D_moveBy(center, (OCT_vec2) { 0, sinf(cycle) });

		OCT_transform2D_moveBy(LB, (OCT_vec2) { -sine, -sine });
		OCT_transform2D_moveBy(LT, (OCT_vec2) { -sine, sine });
		OCT_transform2D_moveBy(RT, (OCT_vec2) { sine, sine });
		OCT_transform2D_moveBy(RB, (OCT_vec2) { sine, -sine });
		//OCT_transform2D_rotateByDeg(center, 1);
		//OCT_transform2D_rotateByDeg(LB, 0.5);
		//OCT_transform2D_rotateByDeg(LT, -0.5);
		//OCT_transform2D_rotateByDeg(RB, -0.5);
		//OCT_transform2D_rotateByDeg(RT, 0.5);


		// OCT_transform2D_rotateByDeg(center, 1);
		//OCT_transform2D_rotateByDeg(child, 1);

		OCT_INPModule_update();
		OCT_ECSModule_update();
		OCT_RENModule_update();
		OCT_WDWModule_update();
	};

	return 0;
}